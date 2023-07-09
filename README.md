# team2-mBot
Arduino and controls code for the mBot Mega

## Installation and deployment

- Need to install the MeMegaPi.h through the Arduino library
- Upload code using Arduino IDE/CLI or VSCode arduino extension

## Testing
Make sure cmake is installed
- To run tests, run the following commands:
```bash
cd LineFollower
./runtests.sh
```
- To run gui need to install conan package manager and make sure to create a profile
```bash
conan profile detect --force
```
- To build and run gui, run the following commands:
```bash
cd LineFollower
conan install . --build=missing
cmake --preset conan-release
./buildgui.sh
```