# GLAD library configuration
# This file defines the glad target

add_library(glad STATIC ${CMAKE_SOURCE_DIR}/external/glad/src/glad.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include)
