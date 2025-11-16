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
        // Define soft pastel colors for each face
        const vec3 softCoral = Color::RGB(1.0f, 0.7f, 0.7f);
        const vec3 softMint = Color::RGB(0.7f, 1.0f, 0.8f);
        const vec3 softLavender = Color::RGB(0.8f, 0.7f, 1.0f);
        const vec3 softPeach = Color::RGB(1.0f, 0.85f, 0.7f);
        const vec3 softSkyBlue = Color::RGB(0.7f, 0.85f, 1.0f);
        const vec3 softRose = Color::RGB(1.0f, 0.75f, 0.85f);

        // Create cube vertices with soft pastel colors for each face
        const Vertices vertices = {
            // Front face (Soft Coral)
            Vertex(vec3(-0.5f, -0.5f, 0.5f), softCoral),
            Vertex(vec3(0.5f, -0.5f, 0.5f), softCoral),
            Vertex(vec3(0.5f, 0.5f, 0.5f), softCoral),
            Vertex(vec3(-0.5f, 0.5f, 0.5f), softCoral),

            // Back face (Soft Mint)
            Vertex(vec3(-0.5f, -0.5f, -0.5f), softMint),
            Vertex(vec3(-0.5f, 0.5f, -0.5f), softMint),
            Vertex(vec3(0.5f, 0.5f, -0.5f), softMint),
            Vertex(vec3(0.5f, -0.5f, -0.5f), softMint),

            // Right face (Soft Lavender)
            Vertex(vec3(0.5f, -0.5f, 0.5f), softLavender),
            Vertex(vec3(0.5f, -0.5f, -0.5f), softLavender),
            Vertex(vec3(0.5f, 0.5f, -0.5f), softLavender),
            Vertex(vec3(0.5f, 0.5f, 0.5f), softLavender),

            // Left face (Soft Peach)
            Vertex(vec3(-0.5f, -0.5f, -0.5f), softPeach),
            Vertex(vec3(-0.5f, -0.5f, 0.5f), softPeach),
            Vertex(vec3(-0.5f, 0.5f, 0.5f), softPeach),
            Vertex(vec3(-0.5f, 0.5f, -0.5f), softPeach),

            // Top face (Soft Sky Blue)
            Vertex(vec3(-0.5f, 0.5f, 0.5f), softSkyBlue),
            Vertex(vec3(0.5f, 0.5f, 0.5f), softSkyBlue),
            Vertex(vec3(0.5f, 0.5f, -0.5f), softSkyBlue),
            Vertex(vec3(-0.5f, 0.5f, -0.5f), softSkyBlue),

            // Bottom face (Soft Rose)
            Vertex(vec3(-0.5f, -0.5f, -0.5f), softRose),
            Vertex(vec3(0.5f, -0.5f, -0.5f), softRose),
            Vertex(vec3(0.5f, -0.5f, 0.5f), softRose),
            Vertex(vec3(-0.5f, -0.5f, 0.5f), softRose)
        };

        // Create cube indices
        const VertexIndices indices = {
            // Front face
            0, 1, 2,
            2, 3, 0,

            // Back face
            4, 5, 6,
            6, 7, 4,

            // Right face
            8, 9, 10,
            10, 11, 8,

            // Left face
            12, 13, 14,
            14, 15, 12,

            // Top face
            16, 17, 18,
            18, 19, 16,

            // Bottom face
            20, 21, 22,
            22, 23, 20
        };

        // Create mesh and shader
        m_CubeMesh = new Mesh(vertices, indices);
        m_Shader = new Shader("shaders/colored/vertex.glsl", "shaders/colored/fragment.glsl");

        // Setup camera
        m_Camera->SetPosition(vec3(0.0f, 0.0f, 3.0f));
        m_Camera->SetProjection(45.0f, 1.0f, 0.1f, 100.0f);
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

        // Set a uniform color when using a basic shader (optional)
        m_Shader->SetVec4("uColor", Color::GrayAlpha(0.7f, 1.0f));

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
