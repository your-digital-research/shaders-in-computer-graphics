#include <vector>

#include "constants/paths.hpp"

#include "view/camera.hpp"
#include "graphics/types.hpp"
#include "examples/scenes/quad_scene.hpp"

namespace examples
{
    using namespace std;
    using namespace glm;

    QuadScene::QuadScene()
        : m_QuadMesh(nullptr),
          m_Shader(nullptr)
    {
        QuadScene::OnCreate();
    }

    QuadScene::~QuadScene()
    {
        QuadScene::OnDestroy();
    }

    void QuadScene::CreateQuad()
    {
        const Vertices vertices = {
            Vertex(vec3(-0.5f, -0.5f, 0.0f), Color::White, vec2(0.0f, 0.0f)),
            Vertex(vec3(0.5f, -0.5f, 0.0f), Color::White, vec2(1.0f, 0.0f)),
            Vertex(vec3(0.5f, 0.5f, 0.0f), Color::White, vec2(1.0f, 1.0f)),
            Vertex(vec3(-0.5f, 0.5f, 0.0f), Color::White, vec2(0.0f, 1.0f)),
        };

        const VertexIndices indices = {
            0, 1, 2,
            0, 2, 3
        };

        m_QuadMesh = new Mesh(vertices, indices);
    }

    void QuadScene::OnCreate()
    {
        CreateQuad();

        // Create Shader
        m_Shader = new Shader(constants::paths::UV_VERTEX_SHADER, constants::paths::UV_FRAGMENT_SHADER);

        // Setup Camera
        m_Camera->SetPosition(vec3(0.0f, 0.0f, 2.5f));
    }

    void QuadScene::OnUpdate(float deltaTime)
    {
        //
    }

    void QuadScene::OnRender()
    {
        // Bind shader and set uniforms
        m_Shader->Bind();
        m_Shader->SetMat4("uModel", mat4(1.0f));
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        // Render quad
        m_QuadMesh->Bind();
        m_QuadMesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void QuadScene::OnDestroy()
    {
        delete m_QuadMesh;
        delete m_Shader;

        m_QuadMesh = nullptr;
        m_Shader = nullptr;
    }
}
