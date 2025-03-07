#! /bin/bash

mkdir -p Build

BUILD_TYPE=$1

if [ -z "$BUILD_TYPE" ]; then
    BUILD_TYPE=LocalDebug
fi

cmake --preset $BUILD_TYPE -S .
cmake --build . --preset $BUILD_TYPE