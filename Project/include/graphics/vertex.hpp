#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "graphics/color.hpp"

namespace graphics
{
    using namespace std;
    using namespace glm;

    // Vertex structure for combined position and color data
    struct Vertex
    {
        vec3 position;
        vec4 color;

        // Constructor with vec4 color (RGBA) - defaults to white
        explicit Vertex(const vec3& pos, const vec4& col = vec4(Color::White, 1.0f))
            : position(pos),
              color(col)
        {
            //
        }

        // Constructor with vec3 color (RGB) - defaults to white with full opacity
        explicit Vertex(const vec3& pos, const vec3& col = Color::White)
            : position(pos),
              color(vec4(col, 1.0f))
        {
            //
        }

        // Constructor with position only - defaults to white
        explicit Vertex(const vec3& pos)
            : position(pos),
              color(vec4(Color::White, 1.0f))
        {
            //
        }
    };

    // Vertex-related type aliases
    using Vertices = vector<Vertex>;
    using VertexPositions = vector<vec3>;
    using VertexColors = vector<vec3>;
    using VertexIndices = vector<unsigned int>;
}
