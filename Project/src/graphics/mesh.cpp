#include "graphics/mesh.hpp"

namespace graphics
{
    using namespace std;
    using namespace glm;

    // Constructor with a Vertex array
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

        // Bind VAO first
        glBindVertexArray(m_VAO);

        // Interleave position and color data
        vector<float> vertexData;
        vertexData.reserve(vertices.size() * 7); // 3 floats for position + 4 for RGBA color

        for (const auto& vertex : vertices)
        {
            // Position (vec3)
            vertexData.push_back(vertex.position.x);
            vertexData.push_back(vertex.position.y);
            vertexData.push_back(vertex.position.z);

            // Color (vec4 - RGBA)
            vertexData.push_back(vertex.color.r);
            vertexData.push_back(vertex.color.g);
            vertexData.push_back(vertex.color.b);
            vertexData.push_back(vertex.color.a);
        }

        // Load interleaved data
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

        // Load index data
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

        constexpr size_t stride = sizeof(vec3) + sizeof(vec4); // position (vec3) + color (vec4)

        // Position attribute
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, static_cast<void*>(nullptr));

        // Color attribute
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<void*>(sizeof(vec3)));

        // Unbind VAO
        glBindVertexArray(0);
    }
}
