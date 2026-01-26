#pragma once

#include <vector>

#include "graphics/color.hpp"

namespace graphics
{
    struct Vertex
    {
        glm::vec3 position;
        Color color;
        glm::vec2 uv;

        explicit Vertex(const glm::vec3& pos, const Color& color = Color::White, const glm::vec2& uv = glm::vec2(0.0f))
            : position(pos), color(color), uv(uv)
        {
            //
        }
    };

    using Vertices = std::vector<Vertex>;
    using VertexIndices = std::vector<unsigned int>;
}
