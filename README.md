# team2-mBot
Arduino and controls code for the mBot Mega.

## Installation and deployment

- Need to install the MeMegaPi.h through the Arduino library
- Upload code using Arduino IDE/CLI or VSCode arduino extension

## Testing
### Googletest
Make sure cmake is installed and might need to install googletest.
```bash
cd LineFollower
./runtests.sh
```
### Dear ImGui
To build gui, need to install conan package manager and create a profile.
```bash
pip install conan
conan profile detect --force
```
Build and run gui.
```bash
cd LineFollower
conan install . --build=missing
cmake --preset conan-release
./buildgui.sh
```