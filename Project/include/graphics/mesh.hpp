#pragma once

#include <vector>

#include <glm/glm.hpp>

#include "graphics/gl.hpp"
#include "graphics/types.hpp"

namespace graphics
{
    using namespace std;
    using namespace glm;

    class Mesh
    {
    public:
        // Constructor and Destructor
        Mesh(const Vertices& vertices, const VertexIndices& indices);
        ~Mesh();

        // Delete copy constructor and assignment operator
        Mesh(const Mesh&) = delete;
        Mesh& operator=(const Mesh&) = delete;

        // Render operations
        void Bind() const;
        void Draw() const;
        static void Unbind();

    private:
        // OpenGL object IDs
        GLuint m_VAO; // Vertex Array Object
        GLuint m_VBO; // Vertex Buffer Object
        GLuint m_IBO; // Index Buffer Object

        // Mesh data
        unsigned int m_IndexCount;

        // Setup method
        void SetupMesh(const Vertices& vertices, const VertexIndices& indices);
    };
}
