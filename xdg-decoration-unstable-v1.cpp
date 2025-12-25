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

#define private public
#define HYPRWAYLAND_SCANNER_NO_INTERFACES
#include "xdg-decoration-unstable-v1.hpp"
#undef private
#define F std::function

static const wl_interface* xdgDecorationUnstableV1_dummyTypes[] = { nullptr };

// Reference all other interfaces.
// The reason why this is in snake is to
// be able to cooperate with existing
// wayland_scanner interfaces (they are interop)
extern const wl_interface zxdg_decoration_manager_v1_interface;
extern const wl_interface zxdg_toplevel_decoration_v1_interface;
extern const wl_interface xdg_toplevel_interface;

static const void* _CCZxdgDecorationManagerV1VTable[] = {
    nullptr,
};

void CCZxdgDecorationManagerV1::sendDestroy() {
    if (!pResource)
        return;
    destroyed = true;

    auto proxy = wl_proxy_marshal_flags(pResource, 0, nullptr, wl_proxy_get_version(pResource), 1);
    proxy;
}

wl_proxy* CCZxdgDecorationManagerV1::sendGetToplevelDecoration(wl_proxy* toplevel) {
    if (!pResource)
        return nullptr;

    auto proxy = wl_proxy_marshal_flags(pResource, 1, &zxdg_toplevel_decoration_v1_interface, wl_proxy_get_version(pResource), 0, nullptr, toplevel);

    return proxy;
}
static const wl_interface* _CZxdgDecorationManagerV1GetToplevelDecorationTypes[] = {
    &zxdg_toplevel_decoration_v1_interface,
    &xdg_toplevel_interface,
};

static const wl_message _CZxdgDecorationManagerV1Requests[] = {
    { .name = "destroy", .signature = "", .types = xdgDecorationUnstableV1_dummyTypes + 0},
    { .name = "get_toplevel_decoration", .signature = "no", .types = _CZxdgDecorationManagerV1GetToplevelDecorationTypes + 0},
};

const wl_interface zxdg_decoration_manager_v1_interface = {
    .name = "zxdg_decoration_manager_v1", .version = 1,
    .method_count = 2, .methods = _CZxdgDecorationManagerV1Requests,
    .event_count = 0, .events = nullptr,
};

CCZxdgDecorationManagerV1::CCZxdgDecorationManagerV1(wl_proxy* resource) : pResource(resource) {

    if (!pResource)
        return;

    wl_proxy_add_listener(pResource, (void (**)(void))&_CCZxdgDecorationManagerV1VTable, this);
}

CCZxdgDecorationManagerV1::~CCZxdgDecorationManagerV1() {
    if (!destroyed)
        sendDestroy();
}

static void _CZxdgToplevelDecorationV1Configure(void* data, void* resource, zxdgToplevelDecorationV1Mode mode) {
    const auto PO = (CCZxdgToplevelDecorationV1*)data;
    if (PO && PO->requests.configure)
        PO->requests.configure(PO, mode);
}

static const void* _CCZxdgToplevelDecorationV1VTable[] = {
    (void*)_CZxdgToplevelDecorationV1Configure,
};

void CCZxdgToplevelDecorationV1::sendDestroy() {
    if (!pResource)
        return;
    destroyed = true;

    auto proxy = wl_proxy_marshal_flags(pResource, 0, nullptr, wl_proxy_get_version(pResource), 1);
    proxy;
}

void CCZxdgToplevelDecorationV1::sendSetMode(zxdgToplevelDecorationV1Mode mode) {
    if (!pResource)
        return;

    auto proxy = wl_proxy_marshal_flags(pResource, 1, nullptr, wl_proxy_get_version(pResource), 0, mode);
    proxy;
}

void CCZxdgToplevelDecorationV1::sendUnsetMode() {
    if (!pResource)
        return;

    auto proxy = wl_proxy_marshal_flags(pResource, 2, nullptr, wl_proxy_get_version(pResource), 0);
    proxy;
}
static const wl_interface* _CZxdgToplevelDecorationV1SetModeTypes[] = {
    nullptr,
};
static const wl_interface* _CZxdgToplevelDecorationV1ConfigureTypes[] = {
    nullptr,
};

static const wl_message _CZxdgToplevelDecorationV1Requests[] = {
    { .name = "destroy", .signature = "", .types = xdgDecorationUnstableV1_dummyTypes + 0},
    { .name = "set_mode", .signature = "u", .types = _CZxdgToplevelDecorationV1SetModeTypes + 0},
    { .name = "unset_mode", .signature = "", .types = xdgDecorationUnstableV1_dummyTypes + 0},
};

static const wl_message _CZxdgToplevelDecorationV1Events[] = {
    { .name = "configure", .signature = "u", .types = _CZxdgToplevelDecorationV1ConfigureTypes + 0},
};

const wl_interface zxdg_toplevel_decoration_v1_interface = {
    .name = "zxdg_toplevel_decoration_v1", .version = 1,
    .method_count = 3, .methods = _CZxdgToplevelDecorationV1Requests,
    .event_count = 1, .events = _CZxdgToplevelDecorationV1Events,
};

CCZxdgToplevelDecorationV1::CCZxdgToplevelDecorationV1(wl_proxy* resource) : pResource(resource) {

    if (!pResource)
        return;

    wl_proxy_add_listener(pResource, (void (**)(void))&_CCZxdgToplevelDecorationV1VTable, this);
}

CCZxdgToplevelDecorationV1::~CCZxdgToplevelDecorationV1() {
    if (!destroyed)
        sendDestroy();
}

void CCZxdgToplevelDecorationV1::setConfigure(F<void(CCZxdgToplevelDecorationV1*, zxdgToplevelDecorationV1Mode)> handler) {
    requests.configure = handler;
}

#undef F
