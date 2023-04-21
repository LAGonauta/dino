#!/bin/bash
./configure --with-libsignal-in-tree --program-prefix=${PWD}/dist --no-debug --release --disable-fast-vapi --with-libsoup3 && \
    make -j$NUMBER_OF_PROCESSORS && \
    make install && \
    cd dist && \
    cp /mingw64/bin/gdbus.exe ./bin && \
    cp /mingw64/bin/gspawn-win64-helper.exe ./bin && \
    cp -r /mingw64/share/xml ./share && \
    cp -r /mingw64/lib/enchant-2 ./lib && \
    cp -r /mingw64/lib/gstreamer-1.0 ./lib && \
    mkdir -p ./etc/fonts && cp -r /mingw64/etc/fonts ./etc/ && \
    mkdir ./share/hunspell && \
    curl -L -o ./share/hunspell/pt_BR.aff https://github.com/elastic/hunspell/raw/master/dicts/pt_BR/pt_BR.aff && \
    curl -L -o ./share/hunspell/pt_BR.dic https://github.com/elastic/hunspell/raw/master/dicts/pt_BR/pt_BR.dic && \
    curl -L -o ./share/hunspell/en_US.aff https://github.com/elastic/hunspell/raw/master/dicts/en_US/en_US.aff && \
    curl -L -o ./share/hunspell/en_US.dic https://github.com/elastic/hunspell/raw/master/dicts/en_US/en_US.dic && \
    mkdir -p ./lib/gdk-pixbuf-2.0/ && cp -r /mingw64/lib/gdk-pixbuf-2.0 ./lib/ && \
    mkdir -p ./lib/gio/ && cp -r /mingw64/lib/gio ./lib/ && \
    mkdir -p ./share/icons && cp -r /mingw64/share/icons ./share/ && \
    mkdir -p ./share/locale && cp -r /mingw64/share/locale ./share/ && \
    mkdir -p ./share/glib-2.0/schemas && cp -r /mingw64/share/glib-2.0/schemas ./share/glib-2.0/ && \
    rm -r ./include && 
    cp /mingw64/bin/libcrypto-*-x64.dll . && \
    find . -iname "*.dll.a" -exec rm {} + && \
    find . -iname "*.exe" -exec ntldd {} + | grep mingw64 | awk '{print "cp /mingw64/bin/"$1" ."}' | sh && \
    find . -iname "*.dll" -exec ntldd {} + | grep mingw64 | awk '{print "cp /mingw64/bin/"$1" ."}' | sh && \
    find . -iname "*.exe" -exec ldd {} + | grep mingw64 | awk '{print "cp /mingw64/bin/"$1" ."}' | sh && \
    find . -iname "*.dll" -exec ldd {} + | grep mingw64 | awk '{print "cp /mingw64/bin/"$1" ."}' | sh && \
    find . -iname "*.exe" -exec strip -s {} + && \
    find . -iname "*.dll" -exec strip -s {} + && \
    mv *.dll ./bin
