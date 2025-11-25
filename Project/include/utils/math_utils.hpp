#pragma once

#include <glm/glm.hpp>

#include "constants/math_constants.hpp"

namespace utils::math
{
    using namespace glm;
    using namespace constants::math;

    // Angle conversions
    constexpr float ToRadians(const float degrees) { return degrees * DEG_TO_RAD; }
    constexpr float ToDegrees(const float radians) { return radians * RAD_TO_DEG; }

    // Clamping
    template <typename T>
    constexpr T Clamp(T value, T min, T max)
    {
        return value < min ? min : (value > max ? max : value);
    }

    // Linear interpolation
    template <typename T>
    constexpr T Lerp(T a, T b, float t)
    {
        return a + (b - a) * t;
    }

    // Smooth step interpolation (cubic Hermite)
    constexpr float SmoothStep(const float edge0, const float edge1, const float x)
    {
        const float t = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);

        return t * t * (3.0f - 2.0f * t);
    }

    // Smoother step interpolation (quintic Hermite)
    constexpr float SmootherStep(const float edge0, const float edge1, const float x)
    {
        const float t = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);

        return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
    }

    // Map value from one range to another
    constexpr float Map(const float value, const float inMin, const float inMax, const float outMin, const float outMax)
    {
        return outMin + (value - inMin) * (outMax - outMin) / (inMax - inMin);
    }

    // Floating point comparison with epsilon
    constexpr bool FloatEqual(const float a, const float b, const float epsilon = EPSILON)
    {
        return abs(a - b) < epsilon;
    }

    // Check if value is power of two
    constexpr bool IsPowerOfTwo(const int value)
    {
        return value > 0 && (value & (value - 1)) == 0;
    }

    // Next power of two
    inline int NextPowerOfTwo(int value)
    {
        value--;

        value |= value >> 1;
        value |= value >> 2;
        value |= value >> 4;
        value |= value >> 8;
        value |= value >> 16;

        return value + 1;
    }

    // Wrap angle to [0, 360]
    inline float WrapAngle360(float angle)
    {
        angle = fmod(angle, 360.0f);

        if (angle < 0.0f) angle += 360.0f;

        return angle;
    }

    // Wrap angle to [-180, 180]
    inline float WrapAngle180(float angle)
    {
        angle = fmod(angle + 180.0f, 360.0f);

        if (angle < 0.0f) angle += 360.0f;

        return angle - 180.0f;
    }

    // Sign function
    template <typename T>
    constexpr int Sign(T value)
    {
        return (T(0) < value) - (value < T(0));
    }

    // Distance between two 2D points
    inline float Distance2D(const vec2& a, const vec2& b)
    {
        return distance(a, b);
    }

    // Distance between two 3D points
    inline float Distance3D(const vec3& a, const vec3& b)
    {
        return distance(a, b);
    }

    // Square of distance (faster, no sqrt)
    inline float DistanceSquared(const vec3& a, const vec3& b)
    {
        const vec3 diff = b - a;

        return dot(diff, diff);
    }
}
