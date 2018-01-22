#!/bin/bash

mkdir build
cd build
CXX=/usr/bin/g++-7 CC=/usr/bin/gcc-7 cmake -DCMAKE_BUILD_TYPE=Coverage ..
make -j2
