# Copyright (c) 2024 Project Nova LLC

rm -rf build
mkdir -p build

arm-apple-darwin11-clang++ -dynamiclib -arch arm64 -o build/libSinum.dylib -framework Foundation