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
        Color color;

        explicit Vertex(const vec3& pos, const Color& color = Color::White)
            : position(pos),
              color(color)
        {
            //
        }
    };

    // Vertex-related type aliases
    using Vertices = vector<Vertex>;
    using VertexPositions = vector<vec3>;
    using VertexColors = vector<Color>;
    using VertexIndices = vector<unsigned int>;
}
