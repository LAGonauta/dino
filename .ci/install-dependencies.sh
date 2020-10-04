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
       make \
       zip

# GPGME 1.13 is not working (crashes), but 1.12 does. However 1.12 does not have a *.pc file. Let's get it from the 1.13 archive.
mkdir temp-gpgme && \
      cd temp-gpgme && \
      #wget http://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-gpgme-1.12.0-1-any.pkg.tar.xz && \
      wget  https://sourceforge.net/projects/msys2/files/REPOS/MINGW/x86_64/mingw-w64-x86_64-gpgme-1.12.0-1-any.pkg.tar.xz && \
      pacman -U --noconfirm ./mingw-w64-x86_64-gpgme-1.12.0-1-any.pkg.tar.xz && \
      #wget http://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-gpgme-1.13.1-4-any.pkg.tar.xz && \
      wget  https://sourceforge.net/projects/msys2/files/REPOS/MINGW/x86_64/mingw-w64-x86_64-gpgme-1.13.1-4-any.pkg.tar.xz && \
      unxz mingw-w64-x86_64-gpgme-1.13.1-4-any.pkg.tar.xz && \
      tar --strip-components=3 -xf mingw-w64-x86_64-gpgme-1.13.1-4-any.pkg.tar mingw64/lib/pkgconfig/gpgme.pc  mingw64/lib/pkgconfig/gpgme-glib.pc && \
      sed -i 's/1.13.1-unknown/1.12.0-unknown/g' *.pc && \
      mv *.pc /mingw64/lib/pkgconfig/ && \
      cd .. && \
      rm -r temp-gpgme
