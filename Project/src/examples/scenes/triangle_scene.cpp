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

    void TriangleScene::OnCreate()
    {
        // Define vertices with positions and colors
        const Vertices vertices = {
            Vertex(vec3(0.0f, 0.5f, 0.0f), Color::Red),             // Top vertex (Red)
            Vertex(vec3(-0.5f, -0.5f, 0.0f), Color::Green),         // Bottom left (Green)
            Vertex(vec3(0.5f, -0.5f, 0.0f), Color::Blue)            // Bottom right (Blue)
        };

        // Create indices
        const VertexIndices indices = {0, 1, 2};

        // Create mesh and shader
        m_TriangleMesh = new Mesh(vertices, indices);
        m_Shader = new Shader(constants::paths::COLORED_VERTEX_SHADER, constants::paths::COLORED_FRAGMENT_SHADER);

        // Setup camera
        m_Camera->SetPosition(vec3(0.0f, 0.0f, 2.5f));
        // m_Camera->SetRotationEuler(vec3(-90.0f, 0.0f, 0.0f));
        // m_Camera->SetProjection(45.0f, 1.0f, 0.1f, 100.0f);
    }

    void TriangleScene::OnUpdate(float deltaTime)
    {
        // No animation for the triangle scene
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
