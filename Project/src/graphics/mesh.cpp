#include "graphics/mesh.hpp"

namespace graphics
{
    using namespace std;
    using namespace glm;

    Mesh::Mesh(const Vertices& vertices, const VertexIndices& indices)
        : m_VAO(0),
          m_VBO(0),
          m_IBO(0),
          m_IndexCount(indices.size())
    {
        SetupMesh(vertices, indices);
    }

    Mesh::~Mesh()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_IBO);
    }

    void Mesh::Bind() const
    {
        glBindVertexArray(m_VAO);
    }

    void Mesh::Draw() const
    {
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);
    }

    void Mesh::Unbind()
    {
        glBindVertexArray(0);
    }

    void Mesh::SetupMesh(const Vertices& vertices, const VertexIndices& indices)
    {
        // Create buffers/arrays
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_IBO);

        // Bind all buffers and load data
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Set up vertex attribute pointers for position, color, and UVs
        glEnableVertexAttribArray(0); // Position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

        glEnableVertexAttribArray(1); // Color
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

        glEnableVertexAttribArray(2); // UVs
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

        // Unbind VAO
        glBindVertexArray(0);
    }
}
