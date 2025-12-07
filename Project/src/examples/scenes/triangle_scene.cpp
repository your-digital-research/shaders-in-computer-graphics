#include <vector>

#include "constants/paths.hpp"

#include "view/camera.hpp"
#include "graphics/types.hpp"
#include "examples/scenes/triangle_scene.hpp"

namespace examples
{
    using namespace std;
    using namespace glm;

    TriangleScene::TriangleScene()
        : m_TriangleMesh(nullptr),
          m_Shader(nullptr),
          m_ModelMatrix(1.0f),
          m_TriangleSize(1.0f),
          m_TopColor(Color::Red),
          m_BottomLeftColor(Color::Green),
          m_BottomRightColor(Color::Blue)
    {
        TriangleScene::OnCreate();
    }

    TriangleScene::~TriangleScene()
    {
        TriangleScene::OnDestroy();
    }

    void TriangleScene::CreateTriangle()
    {
        const float halfSize = m_TriangleSize * 0.5f;

        const Vertices vertices = {
            Vertex(vec3(0.0f, halfSize, 0.0f), m_TopColor, vec2(0.5f, 1.0f)),
            Vertex(vec3(-halfSize, -halfSize, 0.0f), m_BottomLeftColor, vec2(0.0f, 0.0f)),
            Vertex(vec3(halfSize, -halfSize, 0.0f), m_BottomRightColor, vec2(1.0f, 0.0f))
        };

        const VertexIndices indices = {0, 1, 2};

        m_TriangleMesh = new Mesh(vertices, indices);
    }

    void TriangleScene::OnCreate()
    {
        CreateTriangle();

        // Create Shader
        m_Shader = new Shader(constants::paths::COLORED_VERTEX_SHADER, constants::paths::COLORED_FRAGMENT_SHADER);

        // Setup Camera
        m_Camera->SetPosition(vec3(0.0f, 0.0f, 2.5f));
    }

    void TriangleScene::OnUpdate(float deltaTime)
    {
        //
    }

    void TriangleScene::OnRender()
    {
        // Bind shader and set uniforms
        m_Shader->Bind();
        m_Shader->SetMat4("uModel", m_ModelMatrix);
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        // Render triangle
        m_TriangleMesh->Bind();
        m_TriangleMesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void TriangleScene::OnDestroy()
    {
        delete m_TriangleMesh;
        delete m_Shader;

        m_TriangleMesh = nullptr;
        m_Shader = nullptr;
    }
}
