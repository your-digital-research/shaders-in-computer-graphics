#pragma once

#include <vector>

#include "graphics/gl.hpp"
#include <glm/glm.hpp>

namespace graphics
{
    class Mesh
    {
    public:
        // Constructor and Destructor
        Mesh(const std::vector<glm::vec3>& positions,
             const std::vector<unsigned int>& indices);
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

        // Setup
        void SetupMesh(const std::vector<glm::vec3>& positions,
                       const std::vector<unsigned int>& indices);
    };
}
