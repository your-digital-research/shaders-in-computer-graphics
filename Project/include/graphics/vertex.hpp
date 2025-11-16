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
        vec3 color;

        // Constructor with default white color
        explicit Vertex(const vec3& pos, const vec3& col = Color::White)
            : position(pos),
              color(col)
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
