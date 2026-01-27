#pragma once

#include "graphics/gl.hpp"
#include "graphics/types.hpp"

namespace graphics
{
    class Mesh
    {
    public:
        Mesh(const Vertices& vertices, const VertexIndices& indices);
        ~Mesh();

        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        void Bind() const;
        void Draw() const;
        static void Unbind();

    private:
        GLuint m_VAO = 0;
        GLuint m_VBO = 0;
        GLuint m_IBO = 0;

        unsigned int m_IndexCount = 0;

        void SetupMesh(const Vertices& vertices, const VertexIndices& indices);
    };
}
