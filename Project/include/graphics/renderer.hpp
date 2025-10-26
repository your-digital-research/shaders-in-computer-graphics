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
        void Clear() const;
        void SetClearColor(float r, float g, float b, float a) const;

        // OpenGL state management
        static void EnableDepthTest();
        static void DisableDepthTest();

        static void EnableBlending();
        static void DisableBlending();

        static void SetViewport(int x, int y, int width, int height);

    private:
        void Initialize();
    };
}
