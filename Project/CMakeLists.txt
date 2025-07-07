# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name, version and languages
project(ShadersInComputerGraphics VERSION 0.1 LANGUAGES CXX)

# C++ standard (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output path for binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Executable and headers
add_executable(${PROJECT_NAME} src/main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# GLFW
add_subdirectory(external/GLFW)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# macOS-specific OpenGL framework
if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework OpenGL")
endif()