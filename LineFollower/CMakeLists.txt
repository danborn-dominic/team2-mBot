cmake_minimum_required(VERSION 3.10)
project(GuiRobot)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define sources and executable
# TODO: Use recurisve globbing to find all source files
set(SOURCE_FILES
test/guitest.cpp 
src/mock/MockDCMotor.cpp
src/mock/MockEncoder.cpp
src/mock/MockMecanumDrive.cpp
src/MecanumDriveOdometry.cpp
src/MovingFilter.cpp
src/PositionController.cpp) # add all your source files here

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5 REQUIRED COMPONENTS network audio graphics window system)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} sfml-system sfml-window sfml-graphics)
# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Gogole Testing
# Fix weird bug with cmake 3.11 and gtest
cmake_policy(SET CMP0135 NEW)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Add test cpp file
# TODO: Use recurisve globbing to find all test files
add_executable(
  drivetest
  test/drivetest.cpp
)
target_link_libraries(
  drivetest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(drivetest)