#!/bin/sh
# Download the DXVK-native build the port links against (D3D9 -> Vulkan) into
# third_party/dxvk-native. The Makefile copies the 32-bit libdxvk_d3d9.so.0
# next to the executable.
set -e
VER=3.1.1
URL=https://github.com/doitsujin/dxvk/releases/download/v$VER/dxvk-native-$VER-steamrt-sniper.tar.gz
DIR=$(dirname "$(realpath "$0")")/../third_party/dxvk-native
mkdir -p "$DIR"
curl -fL "$URL" | tar xz -C "$DIR"
ls "$DIR/usr/lib32/libdxvk_d3d9.so.0" >/dev/null && echo "DXVK-native $VER -> $DIR"
