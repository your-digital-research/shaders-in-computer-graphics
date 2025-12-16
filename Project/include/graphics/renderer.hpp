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
        static void SetBackgroundColor(const Color& color);

        // OpenGL state management
        static void EnableDepthTest();
        static void DisableDepthTest();
        static void EnableBlending();
        static void DisableBlending();

        // Blend mode management
        static void SetBlendModeAlpha();
        static void SetBlendModeAdditive();
        static void SetBlendModeMultiply();

        // Polygon mode management
        static void SetPolygonModeFill();
        static void SetPolygonModeWireframe();
        static void SetPolygonModePoint();

        // Viewport management
        static void SetViewport(int x, int y, int width, int height);

    private:
        static void Initialize();
    };
}
