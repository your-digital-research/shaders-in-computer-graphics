# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name, version and languages
project(ShadersInComputerGraphics VERSION 0.1 LANGUAGES C CXX)

# C++ standard (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Output path for binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# GLAD
add_library(glad STATIC external/glad/src/glad.c)
target_include_directories(glad PUBLIC external/glad/include)

# GLFW
add_subdirectory(external/GLFW)

# Executable and headers
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glad       # Must come before glfw
        glfw
)

# macOS-specific OpenGL framework
if(APPLE)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            "-framework OpenGL"
    )
endif()