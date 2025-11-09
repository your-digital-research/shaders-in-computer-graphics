#pragma once

#include "graphics/gl.hpp"

namespace graphics
{
    class Renderer
    {
    public:
        // Constructor and Destructor
        Renderer();
        ~Renderer() = default;

        // Render state
        static void Clear();
        static void SetClearColor(float r, float g, float b, float a);

        // OpenGL state management
        static void EnableDepthTest();
        static void DisableDepthTest();
        static void EnableBlending();
        static void DisableBlending();

        // Viewport management
        static void SetViewport(int x, int y, int width, int height);

    private:
        static void Initialize();
    };
}
