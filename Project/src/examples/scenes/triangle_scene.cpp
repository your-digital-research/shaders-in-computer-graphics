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
          m_Shader(nullptr)
    {
        TriangleScene::OnCreate();
    }

    TriangleScene::~TriangleScene()
    {
        TriangleScene::OnDestroy();
    }

    void TriangleScene::CreateTriangle()
    {
        const Vertices vertices = {
            Vertex(vec3(0.0f, 0.5f, 0.0f), Color::Red),
            Vertex(vec3(-0.5f, -0.5f, 0.0f), Color::Green),
            Vertex(vec3(0.5f, -0.5f, 0.0f), Color::Blue)
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
        m_Shader->SetMat4("uModel", mat4(1.0f));
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
