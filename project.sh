#/bin/bash
BUILD_PATH=build
FILE=test

#current_dir=$(pwd)
if [ ! -d "$BUILD_PATH" ]; then
    mkdir "$BUILD_PATH"
fi
cd build
rm -rf *
cmake ..
make

if [ -f "$FILE" ]; then
    cd ..
    cp -r build/test dist/
    rm -rf build/
fi
