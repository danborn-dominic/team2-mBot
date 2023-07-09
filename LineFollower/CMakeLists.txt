cmake_minimum_required(VERSION 3.23)
project(guidrive)

# Add imgui
find_package(imgui REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glew REQUIRED)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
test/imguitest.cpp
src/mock/MockDCMotor.cpp
src/mock/MockEncoder.cpp
src/mock/MockMecanumDrive.cpp
src/MecanumDriveOdometry.cpp
src/MovingFilter.cpp
src/PositionController.cpp)

set(IMGUI_DIR lib/imgui)
set(IMGUI_FILES
${IMGUI_DIR}/opengl_shader.cpp
${IMGUI_DIR}/file_manager.cpp
${IMGUI_DIR}/opengl_shader.h
${IMGUI_DIR}/file_manager.h
${IMGUI_DIR}/bindings/imgui_impl_glfw.cpp
${IMGUI_DIR}/bindings/imgui_impl_glfw.h
${IMGUI_DIR}/bindings/imgui_impl_opengl3.cpp
${IMGUI_DIR}/bindings/imgui_impl_opengl3.h
${IMGUI_DIR}/bindings/imgui_impl_opengl3_loader.h)

include_directories(lib/imgui)

add_executable( ${PROJECT_NAME}
                ${IMGUI_FILES}
                ${SOURCE_FILES})

target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLEW)
target_link_libraries(${PROJECT_NAME} imgui::imgui GLEW::GLEW glfw)

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

set(TEST_SOURCE_FILES 
test/drivetest.cpp
src/mock/MockDCMotor.cpp
src/mock/MockEncoder.cpp
src/mock/MockMecanumDrive.cpp
src/MecanumDriveOdometry.cpp
src/MovingFilter.cpp
src/PositionController.cpp)

# Add test cpp file
add_executable(
  drivetest
  ${TEST_SOURCE_FILES}
)
target_link_libraries(
  drivetest
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(drivetest)
