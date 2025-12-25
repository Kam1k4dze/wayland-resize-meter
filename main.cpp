#include "wayland.hpp"
#include "xdg-shell.hpp"

#include <print>
#include <chrono>
#include <memory>
#include <utility>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>

using namespace std::chrono_literals;

class ResizeMeter
{
public:
    ResizeMeter()
    {
        m_display.reset(wl_display_connect(nullptr));
        if (!m_display) throw std::runtime_error("Failed to connect to display");

        m_registry = std::make_unique<CCWlRegistry>(
            reinterpret_cast<wl_proxy*>(wl_display_get_registry(m_display.get()))
        );

        m_registry->setGlobal([this](CCWlRegistry*, uint32_t name, const char* interface, uint32_t version)
        {
            std::string_view iface = interface;
            if (iface == "wl_compositor")
            {
                m_compositor = std::make_unique<CCWlCompositor>(
                    static_cast<wl_proxy*>(wl_registry_bind(reinterpret_cast<wl_registry*>(m_registry->proxy()), name,
                                                            &wl_compositor_interface, 1))
                );
            }
            else if (iface == "xdg_wm_base")
            {
                m_xdgWmBase = std::make_unique<CCXdgWmBase>(
                    static_cast<wl_proxy*>(wl_registry_bind(reinterpret_cast<wl_registry*>(m_registry->proxy()), name,
                                                            &xdg_wm_base_interface, 1))
                );
                m_xdgWmBase->setPing([](CCXdgWmBase* base, uint32_t serial) { base->sendPong(serial); });
            }
            else if (iface == "wl_shm")
            {
                m_shm = std::make_unique<CCWlShm>(
                    static_cast<wl_proxy*>(wl_registry_bind(reinterpret_cast<wl_registry*>(m_registry->proxy()), name,
                                                            &wl_shm_interface, 1))
                );
            }
        });

        wl_display_roundtrip(m_display.get());

        if (!m_compositor || !m_xdgWmBase || !m_shm)
        {
            throw std::runtime_error("Missing required Wayland globals");
        }

        m_surface = std::make_unique<CCWlSurface>(m_compositor->sendCreateSurface());
        m_xdgSurface = std::make_unique<CCXdgSurface>(m_xdgWmBase->sendGetXdgSurface(m_surface->proxy()));

        m_xdgSurface->setConfigure([this](CCXdgSurface* surface, uint32_t serial)
        {
            surface->sendAckConfigure(serial);
            if (m_hasPendingConfigure)
            {
                updateBuffer(m_pendingWidth ? m_pendingWidth : m_width,
                             m_pendingHeight ? m_pendingHeight : m_height);
                m_hasPendingConfigure = false;
            }
            else if (!m_configured)
            {
                updateBuffer(m_width, m_height);
            }

            auto now = std::chrono::steady_clock::now();
            if (now - m_lastTime >= 1s)
            {
                std::println("Resize events: {}/s", std::exchange(m_resizeEvents, 0));
                m_lastTime = now;
            }
        });

        m_xdgToplevel = std::make_unique<CCXdgToplevel>(m_xdgSurface->sendGetToplevel());
        m_xdgToplevel->setConfigure([this](CCXdgToplevel*, int32_t w, int32_t h, wl_array*)
        {
            m_pendingWidth = w;
            m_pendingHeight = h;
            m_hasPendingConfigure = true;
            m_resizeEvents++;
        });

        m_xdgToplevel->setClose([this](CCXdgToplevel*) { m_running = false; });
        m_xdgToplevel->sendSetTitle("Wayland Resize Meter");
        m_xdgToplevel->sendSetAppId("wayland-resize-meter");
        m_xdgToplevel->sendSetMinSize(200, 200);

        m_surface->sendCommit();
    }

    ~ResizeMeter()
    {
        if (m_poolData && m_poolData != MAP_FAILED) munmap(m_poolData, m_poolSize);
        if (m_fd >= 0) close(m_fd);
    }

    void run()
    {
        while (m_running && wl_display_dispatch(m_display.get()) != -1);
    }

private:
    struct WlDisplayDeleter
    {
        void operator()(wl_display* d) const { wl_display_disconnect(d); }
    };

    std::unique_ptr<wl_display, WlDisplayDeleter> m_display;
    std::unique_ptr<CCWlRegistry> m_registry;
    std::unique_ptr<CCWlCompositor> m_compositor;
    std::unique_ptr<CCXdgWmBase> m_xdgWmBase;
    std::unique_ptr<CCWlShm> m_shm;
    std::unique_ptr<CCWlSurface> m_surface;
    std::unique_ptr<CCXdgSurface> m_xdgSurface;
    std::unique_ptr<CCXdgToplevel> m_xdgToplevel;
    std::unique_ptr<CCWlShmPool> m_pool;
    std::unique_ptr<CCWlBuffer> m_buffer;

    int32_t m_width = 300, m_height = 300;
    int32_t m_pendingWidth = 0, m_pendingHeight = 0;
    bool m_configured = false, m_hasPendingConfigure = false;
    bool m_running = true;
    int m_resizeEvents = 0;
    std::chrono::steady_clock::time_point m_lastTime = std::chrono::steady_clock::now();

    int m_fd = -1;
    size_t m_poolSize = 0;
    void* m_poolData = MAP_FAILED;

    void updateBuffer(int32_t w, int32_t h)
    {
        m_width = w;
        m_height = h;
        m_configured = true;

        const size_t size = w * h * 4;
        if (size > m_poolSize)
        {
            if (m_fd < 0)
            {
                m_fd = memfd_create("wayland-resize-meter", MFD_CLOEXEC);
                if (m_fd < 0)
                {
                    std::println(stderr, "memfd_create failed");
                    return;
                }

                if (ftruncate(m_fd, static_cast<off_t>(size)) < 0)
                {
                    std::println(stderr, "ftruncate failed");
                    close(m_fd);
                    m_fd = -1;
                    return;
                }

                m_poolData = mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, m_fd, 0);
                if (m_poolData == MAP_FAILED)
                {
                    std::println(stderr, "mmap failed");
                    close(m_fd);
                    m_fd = -1;
                    return;
                }

                m_pool = std::make_unique<CCWlShmPool>(m_shm->sendCreatePool(m_fd, static_cast<int32_t>(size)));
                m_poolSize = size;
            }
            else
            {
                if (ftruncate(m_fd, static_cast<off_t>(size)) < 0)
                {
                    std::println(stderr, "ftruncate failed during resize");
                    return;
                }

                m_pool->sendResize(static_cast<int32_t>(size));
                void* newData = mremap(m_poolData, m_poolSize, size, MREMAP_MAYMOVE);
                if (newData == MAP_FAILED)
                {
                    std::println(stderr, "mremap failed");
                    return;
                }

                m_poolData = newData;
                m_poolSize = size;
            }
        }

        m_buffer = std::make_unique<CCWlBuffer>(m_pool->sendCreateBuffer(0, w, h, w * 4, 1));

        if (m_poolData != MAP_FAILED)
        {
            std::memset(m_poolData, 0xFF, size);
        }

        m_surface->sendAttach(m_buffer.get(), 0, 0);
        m_surface->sendDamage(0, 0, w, h);
        m_surface->sendCommit();
    }
};

int main()
{
    try
    {
        ResizeMeter().run();
    }
    catch (const std::exception& e)
    {
        std::println(stderr, "Error: {}", e.what());
        return 1;
    }
}
