#pragma once

namespace constants::math
{
    // Mathematical constants
    constexpr float PI = 3.14159265358979323846f;
    constexpr float TWO_PI = 6.28318530717958647692f;
    constexpr float HALF_PI = 1.57079632679489661923f;
    constexpr float QUARTER_PI = 0.78539816339744830962f;
    constexpr float INV_PI = 0.31830988618379067154f;
    constexpr float E = 2.71828182845904523536f;
    constexpr float SQRT_2 = 1.41421356237309504880f;
    constexpr float SQRT_3 = 1.73205080756887729352f;
    constexpr float GOLDEN_RATIO = 1.61803398874989484820f;

    // Angle conversions
    constexpr float DEG_TO_RAD = PI / 180.0f;
    constexpr float RAD_TO_DEG = 180.0f / PI;

    // Epsilon for floating point comparisons
    constexpr float EPSILON = 1e-6f;
    constexpr float EPSILON_SMALL = 1e-9f;
}
