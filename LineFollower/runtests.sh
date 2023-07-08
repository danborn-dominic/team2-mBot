#!/bin/bash
cd build &&
cmake .. &&
make &&
./GuiRobot;
ctest
