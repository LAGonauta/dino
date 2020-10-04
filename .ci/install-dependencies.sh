#!/bin/bash
pacman -S --needed --noconfirm \
       mingw64/mingw-w64-x86_64-gcc \
       mingw64/mingw-w64-x86_64-cmake \
       mingw64/mingw-w64-x86_64-ninja \
       mingw64/mingw-w64-x86_64-libsoup \
       mingw64/mingw-w64-x86_64-gtk3 \
       mingw64/mingw-w64-x86_64-sqlite3 \
       mingw64/mingw-w64-x86_64-gobject-introspection \
       mingw64/mingw-w64-x86_64-glib2 \
       mingw64/mingw-w64-x86_64-glib-networking \
       mingw64/mingw-w64-x86_64-libgcrypt \
       mingw64/mingw-w64-x86_64-libgee \
       mingw64/mingw-w64-x86_64-pkg-config \
       mingw64/mingw-w64-x86_64-vala \
       mingw64/mingw-w64-x86_64-gsettings-desktop-schemas \
       mingw64/mingw-w64-x86_64-qrencode \
       mingw64/mingw-w64-x86_64-ntldd-git \
       mingw-w64-x86_64-gpgme \
       make \
       zip
