#pragma once

#include <glm/glm.hpp>

namespace graphics
{
    using namespace glm;

    struct Color
    {
        float r, g, b, a;

        constexpr Color() : r(1.0f), g(1.0f), b(1.0f), a(1.0f)
        {
            //
        }

        constexpr Color(const float red, const float green, const float blue, const float alpha = 1.0f)
            : r(red), g(green), b(blue), a(alpha)
        {
            //
        }

        static constexpr Color RGB(float r, float g, float b) { return {r, g, b, 1.0f}; }
        static constexpr Color RGBA(float r, float g, float b, float a) { return {r, g, b, a}; }
        static constexpr Color Gray(float value) { return {value, value, value, 1.0f}; }
        static constexpr Color GrayAlpha(float value, float alpha) { return {value, value, value, alpha}; }

        static constexpr Color RGB255(const int r, const int g, const int b)
        {
            return {
                static_cast<float>(r) / 255.0f,
                static_cast<float>(g) / 255.0f,
                static_cast<float>(b) / 255.0f,
                1.0f
            };
        }

        static constexpr Color RGBA255(const int r, const int g, const int b, const int a)
        {
            return {
                static_cast<float>(r) / 255.0f,
                static_cast<float>(g) / 255.0f,
                static_cast<float>(b) / 255.0f,
                static_cast<float>(a) / 255.0f
            };
        }

        [[nodiscard]] vec3 ToVec3() const { return {r, g, b}; }
        [[nodiscard]] vec4 ToVec4() const { return {r, g, b, a}; }

        explicit operator vec3() const { return ToVec3(); }
        explicit operator vec4() const { return ToVec4(); }

        static const Color White;
        static const Color Black;
        static const Color Red;
        static const Color Green;
        static const Color Blue;
        static const Color Yellow;
        static const Color Cyan;
        static const Color Magenta;
    };

    inline const Color Color::White{1.0f, 1.0f, 1.0f, 1.0f};
    inline const Color Color::Black{0.0f, 0.0f, 0.0f, 1.0f};
    inline const Color Color::Red{1.0f, 0.0f, 0.0f, 1.0f};
    inline const Color Color::Green{0.0f, 1.0f, 0.0f, 1.0f};
    inline const Color Color::Blue{0.0f, 0.0f, 1.0f, 1.0f};
    inline const Color Color::Yellow{1.0f, 1.0f, 0.0f, 1.0f};
    inline const Color Color::Cyan{0.0f, 1.0f, 1.0f, 1.0f};
    inline const Color Color::Magenta{1.0f, 0.0f, 1.0f, 1.0f};
}
