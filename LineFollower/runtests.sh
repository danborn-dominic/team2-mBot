#!/bin/bash
cmake --build --preset conan-release &&
cd build/Release &&
./drivetest
