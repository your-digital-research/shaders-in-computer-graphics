#pragma once

// Silence deprecation warnings on macOS
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

// Include GLAD before GLFW
#include <glad/glad.h>
#include <GLFW/glfw3.h>
