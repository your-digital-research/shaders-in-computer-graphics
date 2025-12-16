# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name, version and languages
project(ShadersInComputerGraphics VERSION 0.1 LANGUAGES C CXX)

# C++ standard (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable parallel build
include(ProcessorCount)
ProcessorCount(N)
if (NOT N EQUAL 0)
    set(CMAKE_BUILD_PARALLEL_LEVEL ${N})
endif ()

# Output path for binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Copy shaders to binary directory
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/bin)

# ---------------------------------------------------------------------------
# GLAD
# ---------------------------------------------------------------------------
include(cmake/glad.cmake)

# ---------------------------------------------------------------------------
# GLFW
# ---------------------------------------------------------------------------
add_subdirectory(external/glfw)

# ---------------------------------------------------------------------------
# GLM
# ---------------------------------------------------------------------------
add_subdirectory(external/glm)

# ---------------------------------------------------------------------------
# ImGui
# ---------------------------------------------------------------------------
include(cmake/imgui.cmake)

# ---------------------------------------------------------------------------
# Executable and headers
# ---------------------------------------------------------------------------
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/external
)

# ---------------------------------------------------------------------------
# Link libraries
# ---------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glad       # Must come before glfw
        glfw
        glm
        imgui
)

# ---------------------------------------------------------------------------
# Platform-specific OpenGL linkage
# ---------------------------------------------------------------------------
if (APPLE)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            "-framework OpenGL"
    )
elseif (WIN32)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            opengl32
    )
else ()
    find_package(OpenGL REQUIRED)
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
            OpenGL::GL
    )
endif ()
