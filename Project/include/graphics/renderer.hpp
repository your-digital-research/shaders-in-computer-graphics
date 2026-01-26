#pragma once

#include "graphics/color.hpp"

namespace graphics
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer() = default;

        static void Clear();
        static void SetBackgroundColor(const Color& color);

        static void EnableDepthTest();
        static void DisableDepthTest();

        static void EnableBlending();
        static void DisableBlending();

        static void SetBlendModeAlpha();
        static void SetBlendModeAdditive();
        static void SetBlendModeMultiply();

        static void SetPolygonModeFill();
        static void SetPolygonModeWireframe();
        static void SetPolygonModePoint();

        static void SetViewport(int x, int y, int width, int height);

    private:
        static void Initialize();
    };
}
