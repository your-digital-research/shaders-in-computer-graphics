#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "graphics/color.hpp"

namespace graphics
{
    using namespace std;
    using namespace glm;

    struct Vertex
    {
        vec3 position;
        Color color;
        vec2 uv;

        explicit Vertex(const vec3& pos, const Color& color = Color::White, const vec2& uv = vec2(0.0f))
            : position(pos), color(color), uv(uv)
        {
            //
        }
    };

    using Vertices = vector<Vertex>;
    using VertexIndices = vector<unsigned int>;
}
