# team2-mBot
Repository for centralized source control for the Arduino code for the mbot mega.

## Installation and deployment

Need to install the MeMegaPi.h through the Arduino library
Upload code using VSCode arduino extension or Arduino IDE/CLI

## Testing
- To do testing need to install SFML GUI Library using a package manager. CMake should be able to locate it.
- Install and use gtest suite. It might install it for you in the CMakeLists but I doubt it.
- To run tests, run the following commands:
```bash
cd LineFollower
./runtests.sh
```
