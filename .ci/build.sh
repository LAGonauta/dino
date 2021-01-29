#!/bin/bash
./configure --with-libsignal-in-tree --program-prefix=${PWD}/dist --no-debug --release --disable-fast-vapi && \
    make -j$NUMBER_OF_PROCESSORS && \
    make install && \
    cd dist && \
    cp /mingw64/bin/gdbus.exe ./bin && \
    cp /mingw64/bin/gspawn-win64-helper.exe ./bin && \
    mkdir -p ./lib/gdk-pixbuf-2.0/ && cp -r /mingw64/lib/gdk-pixbuf-2.0 ./lib/ && \
    mkdir -p ./lib/gio/ && cp -r /mingw64/lib/gio ./lib/ && \
    mkdir -p ./share/icons && cp -r /mingw64/share/icons ./share/ && \
    mkdir -p ./share/locale && cp -r /mingw64/share/locale ./share/ && \
    mkdir -p ./share/glib-2.0/schemas && cp -r /mingw64/share/glib-2.0/schemas ./share/glib-2.0/ && \
    rm -r ./include && 
    find . -iname "*.dll.a" -exec rm {} + && \
    find . -iname "*.exe" -exec ntldd {} + | grep mingw64 | awk '{print "cp /mingw64/bin/"$1" ."}' | sh && \
    find . -iname "*.dll" -exec ntldd {} + | grep mingw64 | awk '{print "cp /mingw64/bin/"$1" ."}' | sh && \
    find . -iname "*.exe" -exec ldd {} + | grep mingw64 | awk '{print "cp /mingw64/bin/"$1" ."}' | sh && \
    find . -iname "*.dll" -exec ldd {} + | grep mingw64 | awk '{print "cp /mingw64/bin/"$1" ."}' | sh && \
    find . -iname "*.exe" -exec strip -s {} + && \
    find . -iname "*.dll" -exec strip -s {} + && \
    mv *.dll ./bin
