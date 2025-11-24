#include <vector>
#include <string>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#include <glm/gtc/matrix_transform.hpp>

#include "view/camera.hpp"
#include "graphics/types.hpp"
#include "examples/scenes/cube_scene.hpp"

namespace examples
{
    using namespace std;
    using namespace glm;
    using namespace graphics;

    CubeScene::CubeScene()
        : m_CubeMesh(nullptr),
          m_Shader(nullptr),
          m_ModelMatrix(1.0f),
          m_RotationAngle(0.0f)
    {
        CubeScene::OnCreate();
    }

    CubeScene::~CubeScene()
    {
        CubeScene::OnDestroy();
    }

    void CubeScene::OnCreate()
    {
        // Create cube vertices
        const Vertices vertices = {
            // Front face
            Vertex(vec3(-0.5f, -0.5f, 0.5f)),
            Vertex(vec3(0.5f, -0.5f, 0.5f)),
            Vertex(vec3(0.5f, 0.5f, 0.5f)),
            Vertex(vec3(-0.5f, 0.5f, 0.5f)),

            // Back face
            Vertex(vec3(-0.5f, -0.5f, -0.5f)),
            Vertex(vec3(-0.5f, 0.5f, -0.5f)),
            Vertex(vec3(0.5f, 0.5f, -0.5f)),
            Vertex(vec3(0.5f, -0.5f, -0.5f))
        };

        // Create cube indices
        const VertexIndices indices = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Right face
            1, 7, 6,
            6, 2, 1,

            // Back face
            7, 4, 5,
            5, 6, 7,

            // Left face
            4, 0, 3,
            3, 5, 4,

            // Top face
            3, 2, 6,
            6, 5, 3,

            // Bottom face
            4, 7, 1,
            1, 0, 4
        };

        // Create mesh and shader
        m_CubeMesh = new Mesh(vertices, indices);
        m_Shader = new Shader("shaders/basic/vertex.glsl", "shaders/basic/fragment.glsl");

        // Setup camera
        m_Camera->SetPosition(vec3(0.0f, 0.0f, 3.0f));
        m_Camera->SetProjection(45.0f, 1.0f, 0.1f, 100.0f); // Initial aspect ratio of 1.0, will be updated
    }

    void CubeScene::OnUpdate(const float deltaTime)
    {
        // Update rotation angle
        m_RotationAngle += deltaTime * 50.0f;

        if (m_RotationAngle >= 360.0f)
        {
            m_RotationAngle -= 360.0f;
        }

        // Update model matrix
        m_ModelMatrix = rotate(mat4(1.0f), radians(m_RotationAngle), vec3(0.5f, 1.0f, 0.0f));
    }

    void CubeScene::OnRender()
    {
        // Bind shader and set uniforms
        m_Shader->Bind();
        m_Shader->SetMat4("uModel", m_ModelMatrix);
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());
        m_Shader->SetVec4("uColor", vec4(0.2f, 0.3f, 0.8f, 1.0f));

        // Render cube
        m_CubeMesh->Bind();
        m_CubeMesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void CubeScene::OnDestroy()
    {
        delete m_CubeMesh;
        delete m_Shader;

        m_CubeMesh = nullptr;
        m_Shader = nullptr;
    }
}
