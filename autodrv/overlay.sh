#!/bin/bash

# Get sudo privileges
sudo -v

# Disable console blanking and power saving
TERM=linux setterm -blank 0 -powerdown 0 -powersave off > /dev/tty0 < /dev/tty0

# Set framebuffer properties for /dev/fb1
fbset -fb /dev/fb1 -xres 1024 -yres 600 -depth 32 -vyres 600 -t 31250 40 40 29 13 48 3

# Disable blanking for /dev/fb1 and /dev/fb0
echo 0 > /sys/class/graphics/fb1/blank
echo 0 > /sys/class/graphics/fb0/blank