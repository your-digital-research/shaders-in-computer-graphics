#include "graphics/color.hpp"

namespace graphics
{
    // Define predefined colors
    const vec3 Color::White(1.0f, 1.0f, 1.0f);
    const vec3 Color::Black(0.0f, 0.0f, 0.0f);
    const vec3 Color::Red(1.0f, 0.0f, 0.0f);
    const vec3 Color::Green(0.0f, 1.0f, 0.0f);
    const vec3 Color::Blue(0.0f, 0.0f, 1.0f);
    const vec3 Color::Yellow(1.0f, 1.0f, 0.0f);
    const vec3 Color::Cyan(0.0f, 1.0f, 1.0f);
    const vec3 Color::Magenta(1.0f, 0.0f, 1.0f);

    // RGB constructor implementations (vec3)
    vec3 Color::RGB(const float r, const float g, const float b)
    {
        return vec3(r, g, b);
    }

    vec3 Color::RGB255(const int r, const int g, const int b)
    {
        return vec3(r / 255.0f, g / 255.0f, b / 255.0f);
    }

    vec3 Color::Gray(const float value)
    {
        return vec3(value, value, value);
    }

    // RGBA constructor implementations (vec4)
    vec4 Color::RGBA(const float r, const float g, const float b, const float a)
    {
        return vec4(r, g, b, a);
    }

    vec4 Color::RGBA255(const int r, const int g, const int b, const int a)
    {
        return vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }

    vec4 Color::GrayAlpha(const float value, const float alpha)
    {
        return vec4(value, value, value, alpha);
    }
}

