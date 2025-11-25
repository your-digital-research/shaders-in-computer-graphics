#pragma once

namespace constants::graphics
{
    // Default window settings
    constexpr int DEFAULT_WINDOW_WIDTH = 1280;
    constexpr int DEFAULT_WINDOW_HEIGHT = 720;
    constexpr char DEFAULT_WINDOW_TITLE[] = "Shaders In Computer Graphics";

    // OpenGL version
    constexpr int OPENGL_MAJOR_VERSION = 3;
    constexpr int OPENGL_MINOR_VERSION = 3;

    // Camera defaults
    constexpr float DEFAULT_FOV = 45.0f;
    constexpr float DEFAULT_NEAR_PLANE = 0.1f;
    constexpr float DEFAULT_FAR_PLANE = 100.0f;
    constexpr float DEFAULT_CAMERA_SPEED = 2.5f;
    constexpr float DEFAULT_MOUSE_SENSITIVITY = 0.1f;

    // Rendering defaults
    constexpr int DEFAULT_MSAA_SAMPLES = 4;
    constexpr bool DEFAULT_VSYNC = true;
    constexpr bool DEFAULT_DEPTH_TEST = true;
    constexpr bool DEFAULT_BLENDING = false;

    // Mesh defaults
    constexpr int DEFAULT_VERTEX_BUFFER_SIZE = 1024;
    constexpr int DEFAULT_INDEX_BUFFER_SIZE = 2048;
}
