// Generated with hyprwayland-scanner 0.4.5. Made with vaxry's keyboard and ❤️.
// xdg_decoration_unstable_v1

/*
 This protocol's authors' copyright notice is:


    Copyright © 2018 Simon Ser

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice (including the next
    paragraph) shall be included in all copies or substantial portions of the
    Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
    DEALINGS IN THE SOFTWARE.
  
*/

#pragma once

#include <functional>
#include <cstdint>
#include <string>
#include <wayland-client.h>

#define F std::function

struct wl_proxy;

enum zxdgToplevelDecorationV1Error : uint32_t {
    ZXDG_TOPLEVEL_DECORATION_V1_ERROR_UNCONFIGURED_BUFFER = 0,
    ZXDG_TOPLEVEL_DECORATION_V1_ERROR_ALREADY_CONSTRUCTED = 1,
    ZXDG_TOPLEVEL_DECORATION_V1_ERROR_ORPHANED = 2,
    ZXDG_TOPLEVEL_DECORATION_V1_ERROR_INVALID_MODE = 3,
};

enum zxdgToplevelDecorationV1Mode : uint32_t {
    ZXDG_TOPLEVEL_DECORATION_V1_MODE_CLIENT_SIDE = 1,
    ZXDG_TOPLEVEL_DECORATION_V1_MODE_SERVER_SIDE = 2,
};


class CCZxdgDecorationManagerV1;
class CCZxdgToplevelDecorationV1;
class CCXdgToplevel;
class CCZxdgToplevelDecorationV1;

#ifndef HYPRWAYLAND_SCANNER_NO_INTERFACES
extern const wl_interface zxdg_decoration_manager_v1_interface;
extern const wl_interface zxdg_toplevel_decoration_v1_interface;

#endif


class CCZxdgDecorationManagerV1 {
  public:
    CCZxdgDecorationManagerV1(wl_proxy*);
    ~CCZxdgDecorationManagerV1();


    // set the data for this resource
    void setData(void* data) {{
        pData = data;
    }}

    // get the data for this resource
    void* data() {{
        return pData;
    }}

    // get the raw wl_resource (wl_proxy) ptr
    wl_proxy* resource() {{
        return pResource;
    }}

    // get the raw wl_proxy ptr
    wl_proxy* proxy() {{
        return pResource;
    }}

    // get the resource version
    int version() {{
        return wl_proxy_get_version(pResource);
    }}
            
    // --------------- Requests --------------- //


    // --------------- Events --------------- //

    void sendDestroy();
    wl_proxy* sendGetToplevelDecoration(wl_proxy*);

  private:
    struct {
    } requests;

    wl_proxy* pResource = nullptr;

    bool destroyed = false;

    void* pData = nullptr;
};



class CCZxdgToplevelDecorationV1 {
  public:
    CCZxdgToplevelDecorationV1(wl_proxy*);
    ~CCZxdgToplevelDecorationV1();


    // set the data for this resource
    void setData(void* data) {{
        pData = data;
    }}

    // get the data for this resource
    void* data() {{
        return pData;
    }}

    // get the raw wl_resource (wl_proxy) ptr
    wl_proxy* resource() {{
        return pResource;
    }}

    // get the raw wl_proxy ptr
    wl_proxy* proxy() {{
        return pResource;
    }}

    // get the resource version
    int version() {{
        return wl_proxy_get_version(pResource);
    }}
            
    // --------------- Requests --------------- //

    void setConfigure(F<void(CCZxdgToplevelDecorationV1*, zxdgToplevelDecorationV1Mode)> handler);

    // --------------- Events --------------- //

    void sendDestroy();
    void sendSetMode(zxdgToplevelDecorationV1Mode);
    void sendUnsetMode();

  private:
    struct {
        F<void(CCZxdgToplevelDecorationV1*, zxdgToplevelDecorationV1Mode)> configure;
    } requests;

    wl_proxy* pResource = nullptr;

    bool destroyed = false;

    void* pData = nullptr;
};



#undef F
