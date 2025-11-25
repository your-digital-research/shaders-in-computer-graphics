#include <vector>
#include <string>

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#include <glm/gtc/matrix_transform.hpp>

#include "constants/paths.hpp"
#include "utils/math_utils.hpp"

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
        constexpr Color softCoral = Color::RGBA(1.0f, 0.7f, 0.7f, 1.0f);
        constexpr Color softMint = Color::RGBA(0.7f, 1.0f, 0.8f, 1.0f);
        constexpr Color softLavender = Color::RGBA(0.8f, 0.7f, 1.0f, 1.0f);
        constexpr Color softPeach = Color::RGBA(1.0f, 0.85f, 0.7f, 1.0f);
        constexpr Color softSkyBlue = Color::RGBA(0.7f, 0.85f, 1.0f, 1.0f);
        constexpr Color softRose = Color::RGBA(1.0f, 0.75f, 0.85f, 1.0f);

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
        m_Shader = new Shader(constants::paths::COLORED_VERTEX_SHADER, constants::paths::COLORED_FRAGMENT_SHADER);

        // Setup camera
        m_Camera->SetPosition(vec3(0.0f, 0.0f, 4.0f));
        // m_Camera->SetRotationEuler(vec3(-90.0f, 0.0f, 0.0f));
        // m_Camera->SetProjection(45.0f, 1.0f, 0.1f, 100.0f);
    }

    void CubeScene::OnUpdate(const float deltaTime)
    {
        // Update rotation angle
        m_RotationAngle += deltaTime * 50.0f;

        // Use utility to wrap an angle to [0, 360]
        m_RotationAngle = utils::math::WrapAngle360(m_RotationAngle);

        // Update model matrix using math utility for conversion
        m_ModelMatrix = rotate(mat4(1.0f), utils::math::ToRadians(m_RotationAngle), vec3(0.5f, 1.0f, 0.0f));
    }

    void CubeScene::OnRender()
    {
        // Bind shader and set uniforms
        m_Shader->Bind();
        m_Shader->SetMat4("uModel", m_ModelMatrix);
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        // Set a uniform color when using a basic shader (not used in colored shader)
        constexpr Color color = Color::GrayAlpha(0.7f, 1.0f);
        // m_Shader->SetVec4("uColor", color.ToVec4());

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
