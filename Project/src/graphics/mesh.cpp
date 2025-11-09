#include "graphics/mesh.hpp"

namespace graphics
{
    Mesh::Mesh(
        const std::vector<glm::vec3>& positions,
        const std::vector<unsigned int>& indices)
        : m_VAO(0),
          m_VBO(0),
          m_IBO(0),
          m_IndexCount(indices.size())
    {
        SetupMesh(positions, indices);
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

    void Mesh::SetupMesh(const std::vector<glm::vec3>& positions, const std::vector<unsigned int>& indices)
    {
        // Create buffers/arrays
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_IBO);

        // Bind VAO first
        glBindVertexArray(m_VAO);

        // Load vertex data
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);

        // Load index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Set vertex attribute pointers
        // Position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), static_cast<void*>(nullptr));

        // Unbind VAO
        glBindVertexArray(0);
    }
}
