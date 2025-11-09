#include "graphics/mesh.hpp"

namespace graphics
{
    Mesh::Mesh(const std::vector<glm::vec3>& positions,
               const std::vector<unsigned int>& indices,
               const std::vector<glm::vec3>& colors)
        : m_VAO(0),
          m_VBO(0),
          m_IBO(0),
          m_IndexCount(indices.size())
    {
        SetupMesh(positions, indices, colors);
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

    void Mesh::SetupMesh(const std::vector<glm::vec3>& positions,
                         const std::vector<unsigned int>& indices,
                         const std::vector<glm::vec3>& colors)
    {
        // Create buffers/arrays
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
        glGenBuffers(1, &m_IBO);

        // Bind VAO first
        glBindVertexArray(m_VAO);

        const bool hasColors = !colors.empty();
        const size_t stride = hasColors ? sizeof(glm::vec3) * 2 : sizeof(glm::vec3);

        if (hasColors)
        {
            // Interleave position and color data
            std::vector<float> vertexData;
            vertexData.reserve(positions.size() * 6); // 3 floats for position + 3 for color

            for (size_t i = 0; i < positions.size(); i++)
            {
                // Position
                vertexData.push_back(positions[i].x);
                vertexData.push_back(positions[i].y);
                vertexData.push_back(positions[i].z);

                // Color
                vertexData.push_back(colors[i].x);
                vertexData.push_back(colors[i].y);
                vertexData.push_back(colors[i].z);
            }

            // Load interleaved data
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
        }
        else
        {
            // Load position data only
            glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
            glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), positions.data(), GL_STATIC_DRAW);
        }

        // Load index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        // Set vertex attribute pointers
        // Position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, static_cast<void*>(nullptr));

        // Color attribute (if present)
        if (hasColors)
        {
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(sizeof(glm::vec3)));
        }

        // Unbind VAO
        glBindVertexArray(0);
    }
}
