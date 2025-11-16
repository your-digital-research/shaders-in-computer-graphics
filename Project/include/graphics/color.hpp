#pragma once

#include <glm/glm.hpp>

namespace graphics
{
    using namespace glm;

    // Color helper struct with predefined colors and constructors
    struct Color
    {
        // Predefined colors
        static const vec3 White;
        static const vec3 Black;
        static const vec3 Red;
        static const vec3 Green;
        static const vec3 Blue;
        static const vec3 Yellow;
        static const vec3 Cyan;
        static const vec3 Magenta;

        // RGB constructors (vec3 - no alpha)
        // RGB constructor (values 0.0 to 1.0)
        static vec3 RGB(float r, float g, float b);

        // RGB constructor with integer values (0 to 255)
        static vec3 RGB255(int r, int g, int b);

        // Grayscale constructor
        static vec3 Gray(float value);

        // RGBA constructors (vec4 - with alpha)
        // RGBA constructor (values 0.0 to 1.0)
        static vec4 RGBA(float r, float g, float b, float a);

        // RGBA constructor with integer values (0 to 255)
        static vec4 RGBA255(int r, int g, int b, int a);

        // Grayscale with alpha constructor
        static vec4 GrayAlpha(float value, float alpha);
    };
}
