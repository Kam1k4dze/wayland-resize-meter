# Wayland Resize Meter

Measures Wayland window resize events per second.

## Build

```sh
c++ -std=c++23 -O2 main.cpp wayland.cpp xdg-shell.cpp -o wayland-resize-meter -lwayland-client
./wayland-resize-meter
```

