#pragma once

#include <glm/glm.hpp>

#include "graphics/gl.hpp"
#include "graphics/color.hpp"

namespace graphics
{
    using namespace glm;

    class Renderer
    {
    public:
        // Constructor and Destructor
        Renderer();
        ~Renderer() = default;

        // Render state
        static void Clear();
        static void SetClearColor(const Color& color);

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
