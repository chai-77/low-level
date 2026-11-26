#!/bin/bash
# input the name of file in commadline argument
file=$1
argc=$2

if [ -z "$file" ]; then
    echo "Usage: ./run.sh filename.cpp [arguments]"
    exit 1
fi

# search entire directory recursivly
found=$(find . -name "$file" -print -quit)

if [ -z "$found" ]; then
    echo "file not found"
    exit 1
fi

# compile that file. keep the op in build 

name=$(basename "$found" .cpp)

mkdir -p build

echo "compiling $found"

g++ -fopenmp "$found" -o "build/$name"

# run the build

if [ $? -eq 0 ]; then

    echo "Running: $name"

    # pass all arguments after the filename
    "./build/$name" "${@:2}"

else
    echo "Compilation failed!"
    exit 1
fi
