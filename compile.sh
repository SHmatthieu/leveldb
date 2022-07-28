#! /bin/bash 
rm -fr build && mkdir build && cd build
cmake -DWASI_SDK_PREFIX=$WASI_SDK_PATH -DCMAKE_TOOLCHAIN_FILE=$WASI_SDK_PATH/share/cmake/wasi-sdk.cmake -DCMAKE_SYSROOT=$WASI_SDK_PATH/share/wasi-sysroot -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
cd ..
