#include "examples/scenes/sphere_scene.hpp"

#include <cmath>
#include <string>
#include <vector>

#include <glm/gtc/matrix_transform.hpp>

#include "constants/math_constants.hpp"
#include "constants/paths.hpp"
#include "graphics/types.hpp"
#include "utils/math_utils.hpp"

namespace examples
{
    SphereScene::SphereScene()
        : m_SphereMesh(nullptr),
          m_Shader(nullptr),
          m_ModelMatrix(1.0f),
          m_RotationAngle(0.0f),
          m_RotationSpeed(16.0f),
          m_PulseSpeed(2.0f),
          m_Time(0.0f),
          m_SphereRadius(1.0f),
          m_Segments(64),
          m_Rings(32),
          m_RimPower(2.0f),
          m_RimIntensity(4.0f),
          m_CurrentColorTheme(SphereColorTheme::DeepSpace)
    {
        SetColorTheme(m_CurrentColorTheme);

        SphereScene::OnCreate();
    }

    SphereScene::~SphereScene()
    {
        SphereScene::OnDestroy();
    }

    void SphereScene::CreateSphere(const float radius, const unsigned int segments, const unsigned int rings)
    {
        Vertices vertices;
        VertexIndices indices;

        // Generate sphere vertices using spherical coordinates
        for (unsigned int ring = 0; ring <= rings; ++ring)
        {
            const float phi = constants::math::PI * static_cast<float>(ring) / static_cast<float>(rings);
            const float y = radius * glm::cos(phi);
            const float ringRadius = radius * glm::sin(phi);

            for (unsigned int seg = 0; seg <= segments; ++seg)
            {
                const float theta = constants::math::TWO_PI * static_cast<float>(seg) / static_cast<float>(segments);
                const float x = ringRadius * glm::cos(theta);
                const float z = ringRadius * glm::sin(theta);

                const glm::vec3 position(x, y, z);
                const float u = static_cast<float>(seg) / static_cast<float>(segments);
                const float v = static_cast<float>(ring) / static_cast<float>(rings);

                vertices.emplace_back(position, Color::White, glm::vec2(u, v));
            }
        }

        // Generate triangle indices
        for (unsigned int ring = 0; ring < rings; ++ring)
        {
            for (unsigned int seg = 0; seg < segments; ++seg)
            {
                const unsigned int current = ring * (segments + 1) + seg;
                const unsigned int next = current + segments + 1;

                indices.push_back(current);
                indices.push_back(next);
                indices.push_back(current + 1);

                indices.push_back(current + 1);
                indices.push_back(next);
                indices.push_back(next + 1);
            }
        }

        m_SphereMesh = new Mesh(vertices, indices);
    }

    void SphereScene::OnCreate()
    {
        CreateSphere(m_SphereRadius, m_Segments, m_Rings);

        m_Shader = new Shader(constants::paths::FRESNEL_VERTEX_SHADER,
                              constants::paths::FRESNEL_FRAGMENT_SHADER);

        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
    }

    void SphereScene::OnUpdate(const float deltaTime)
    {
        m_Time += deltaTime * m_PulseSpeed;
        m_RotationAngle += deltaTime * m_RotationSpeed;
        m_RotationAngle = utils::math::WrapAngle360(m_RotationAngle);

        m_ModelMatrix = glm::rotate(glm::mat4(1.0f), utils::math::ToRadians(m_RotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    }

    void SphereScene::OnRender()
    {
        m_Shader->Bind();

        m_Shader->SetMat4("uModel", m_ModelMatrix);
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        m_Shader->SetVec3("uCameraPos", m_Camera->GetPosition());

        m_Shader->SetFloat("uTime", m_Time);
        m_Shader->SetFloat("uPulseSpeed", m_PulseSpeed);
        m_Shader->SetFloat("uRimPower", m_RimPower);
        m_Shader->SetFloat("uRimIntensity", m_RimIntensity);

        m_Shader->SetVec4("uRimColor", m_RimColor.ToVec4());
        m_Shader->SetVec4("uCoreColor", m_CoreColor.ToVec4());

        m_SphereMesh->Bind();
        m_SphereMesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void SphereScene::OnDestroy()
    {
        delete m_SphereMesh;
        delete m_Shader;

        m_SphereMesh = nullptr;
        m_Shader = nullptr;
    }

    void SphereScene::SetColorTheme(const SphereColorTheme theme)
    {
        m_CurrentColorTheme = theme;

        switch (theme)
        {
        case SphereColorTheme::Unknown:
            m_RimColor = Color::White;
            m_CoreColor = Color::White;
            break;

        case SphereColorTheme::CyberGlow:
            m_RimColor = Color::RGB(0.3f, 0.8f, 1.0f); // Bright cyan
            m_CoreColor = Color::RGB(0.15f, 0.1f, 0.3f); // Deep purple
            break;

        case SphereColorTheme::FireBall:
            m_RimColor = Color::RGB(1.0f, 0.5f, 0.0f); // Bright orange
            m_CoreColor = Color::RGB(0.5f, 0.0f, 0.0f); // Dark red
            break;

        case SphereColorTheme::IceSphere:
            m_RimColor = Color::RGB(0.7f, 0.9f, 1.0f); // Light blue
            m_CoreColor = Color::RGB(0.1f, 0.2f, 0.3f); // Deep blue
            break;

        case SphereColorTheme::NeonPink:
            m_RimColor = Color::RGB(1.0f, 0.2f, 0.8f); // Hot pink
            m_CoreColor = Color::RGB(0.2f, 0.0f, 0.2f); // Dark magenta
            break;

        case SphereColorTheme::EnergyShield:
            m_RimColor = Color::RGB(0.0f, 1.0f, 0.5f); // Bright green
            m_CoreColor = Color::RGB(0.0f, 0.2f, 0.1f); // Dark green
            break;

        case SphereColorTheme::AuroraBorealis:
            m_RimColor = Color::RGB(0.4f, 1.0f, 0.9f); // Cyan-green
            m_CoreColor = Color::RGB(0.4f, 0.15f, 0.6f); // Purple
            break;

        case SphereColorTheme::SunsetGlow:
            m_RimColor = Color::RGB(1.0f, 0.6f, 0.3f); // Orange
            m_CoreColor = Color::RGB(0.6f, 0.2f, 0.4f); // Deep pink
            break;

        case SphereColorTheme::ToxicWaste:
            m_RimColor = Color::RGB(0.8f, 1.0f, 0.0f); // Yellow-green
            m_CoreColor = Color::RGB(0.1f, 0.4f, 0.0f); // Dark green
            break;

        case SphereColorTheme::DeepSpace:
            m_RimColor = Color::RGB(1.0f, 1.0f, 1.0f); // White
            m_CoreColor = Color::RGB(0.05f, 0.0f, 0.2f); // Dark purple
            break;

        case SphereColorTheme::HologramBlue:
            m_RimColor = Color::RGB(0.2f, 0.7f, 1.0f); // Electric blue
            m_CoreColor = Color::RGB(0.1f, 0.1f, 0.3f); // Dark blue
            break;
        }
    }
}
