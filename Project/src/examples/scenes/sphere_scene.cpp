#include "examples/scenes/sphere_scene.hpp"

#include <cmath>
#include <vector>

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "constants/math_constants.hpp"
#include "constants/paths.hpp"
#include "utils/math_utils.hpp"

namespace examples
{
    SphereScene::SphereScene(Camera* camera)
        : Scene(camera)
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
        if (m_Mesh != nullptr)
        {
            delete m_Mesh;

            m_Mesh = nullptr;
        }

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

        m_Mesh = new Mesh(vertices, indices);
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
        if (m_Mesh == nullptr || m_Shader == nullptr) return;

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

        m_Mesh->Bind();
        m_Mesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void SphereScene::OnDestroy()
    {
        delete m_Mesh;
        delete m_Shader;

        m_Mesh = nullptr;
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

    void SphereScene::SetSphereRadius(const float radius)
    {
        m_SphereRadius = glm::max(0.1f, radius);

        CreateSphere(m_SphereRadius, m_Segments, m_Rings);
    }

    void SphereScene::SetSegments(const int segments)
    {
        m_Segments = glm::max(3, segments);

        CreateSphere(m_SphereRadius, m_Segments, m_Rings);
    }

    void SphereScene::SetRings(const int rings)
    {
        m_Rings = glm::max(2, rings);

        CreateSphere(m_SphereRadius, m_Segments, m_Rings);
    }

    void SphereScene::SetRotationSpeed(const float speed)
    {
        m_RotationSpeed = speed;
    }

    void SphereScene::SetPulseSpeed(const float speed)
    {
        m_PulseSpeed = speed;
    }

    void SphereScene::SetRimIntensity(const float intensity)
    {
        m_RimIntensity = glm::max(0.0f, intensity);
    }

    void SphereScene::SetRimPower(const float power)
    {
        m_RimPower = glm::max(0.1f, power);
    }

    void SphereScene::SetCoreColor(const Color& color)
    {
        m_CoreColor = color;
        m_CurrentColorTheme = SphereColorTheme::Unknown;
    }

    void SphereScene::SetRimColor(const Color& color)
    {
        m_RimColor = color;
        m_CurrentColorTheme = SphereColorTheme::Unknown;
    }

    void SphereScene::ResetToDefault()
    {
        m_SphereRadius = m_DefaultSphereRadius;
        m_Segments = m_DefaultSegments;
        m_Rings = m_DefaultRings;

        m_RotationSpeed = m_DefaultRotationSpeed;
        m_PulseSpeed = m_DefaultPulseSpeed;

        m_RimIntensity = m_DefaultRimIntensity;
        m_RimPower = m_DefaultRimPower;

        m_RotationAngle = 0.0f;
        m_Time = 0.0f;

        SetColorTheme(m_DefaultColorTheme);

        m_Camera->SetPosition(m_DefaultCameraPosition);
        m_Camera->SetRotationEuler(m_DefaultCameraRotation);

        CreateSphere(m_SphereRadius, m_Segments, m_Rings);
    }

    void SphereScene::RenderSettings()
    {
        constexpr float panelWidth = 340.0f;
        constexpr float panelHeight = 480.0f;
        constexpr float padding = 10.0f;

        const ImGuiIO& io = ImGui::GetIO();
        const float xPos = io.DisplaySize.x - panelWidth - padding;
        const float yPos = io.DisplaySize.y - panelHeight - padding;

        ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

        ImGui::Begin("Scene Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Sphere Properties");
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Sphere Radius
        float sphereRadius = m_SphereRadius;
        if (ImGui::SliderFloat("Radius", &sphereRadius, 0.1f, 5.0f, "%.2f"))
        {
            SetSphereRadius(sphereRadius);
        }

        // Segments
        int segments = m_Segments;
        if (ImGui::SliderInt("Segments", &segments, 3, 128))
        {
            SetSegments(segments);
        }

        // Rings
        int rings = m_Rings;
        if (ImGui::SliderInt("Rings", &rings, 2, 128))
        {
            SetRings(rings);
        }

        // Rotation Speed
        float rotationSpeed = m_RotationSpeed;
        if (ImGui::SliderFloat("Rotation Speed", &rotationSpeed, -180.0f, 180.0f, "%.1f°/s"))
        {
            SetRotationSpeed(rotationSpeed);
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Effect Properties");
        ImGui::Spacing();

        // Rim Power
        float rimPower = m_RimPower;
        if (ImGui::SliderFloat("Rim Power", &rimPower, 0.1f, 10.0f, "%.2f"))
        {
            SetRimPower(rimPower);
        }

        // Rim Intensity
        float rimIntensity = m_RimIntensity;
        if (ImGui::SliderFloat("Rim Intensity", &rimIntensity, 0.0f, 10.0f, "%.2f"))
        {
            SetRimIntensity(rimIntensity);
        }

        // Pulse Speed
        float pulseSpeed = m_PulseSpeed;
        if (ImGui::SliderFloat("Pulse Speed", &pulseSpeed, 0.0f, 10.0f, "%.2f"))
        {
            SetPulseSpeed(pulseSpeed);
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Color Theme Selection
        ImGui::Text("Color Theme");
        ImGui::Spacing();

        const char* themeNames[] = {
            "Custom",
            "Cyber Glow",
            "Fire Ball",
            "Ice Sphere",
            "Neon Pink",
            "Energy Shield",
            "Aurora Borealis",
            "Sunset Glow",
            "Toxic Waste",
            "Deep Space",
            "Hologram Blue"
        };

        constexpr SphereColorTheme themes[] = {
            SphereColorTheme::Unknown,
            SphereColorTheme::CyberGlow,
            SphereColorTheme::FireBall,
            SphereColorTheme::IceSphere,
            SphereColorTheme::NeonPink,
            SphereColorTheme::EnergyShield,
            SphereColorTheme::AuroraBorealis,
            SphereColorTheme::SunsetGlow,
            SphereColorTheme::ToxicWaste,
            SphereColorTheme::DeepSpace,
            SphereColorTheme::HologramBlue
        };

        int currentThemeIndex = 0;
        for (int i = 0; i < 11; i++)
        {
            if (m_CurrentColorTheme == themes[i])
            {
                currentThemeIndex = i;

                break;
            }
        }

        if (ImGui::Combo("Preset", &currentThemeIndex, themeNames, IM_ARRAYSIZE(themeNames)))
        {
            SetColorTheme(themes[currentThemeIndex]);
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Individual Color Controls
        ImGui::Text("Custom Colors");
        ImGui::Spacing();

        // Rim Color
        float rimColor[3] = {m_RimColor.r, m_RimColor.g, m_RimColor.b};
        if (ImGui::ColorEdit3("Rim", rimColor))
        {
            SetRimColor(Color::RGB(rimColor[0], rimColor[1], rimColor[2]));
        }

        // Core Color
        float coreColor[3] = {m_CoreColor.r, m_CoreColor.g, m_CoreColor.b};
        if (ImGui::ColorEdit3("Core", coreColor))
        {
            SetCoreColor(Color::RGB(coreColor[0], coreColor[1], coreColor[2]));
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        constexpr float buttonHeight = 30.0f;
        if (const float availableHeight = ImGui::GetContentRegionAvail().y; availableHeight > buttonHeight)
        {
            ImGui::Dummy(ImVec2(0.0f, availableHeight - buttonHeight));
        }

        if (ImGui::Button("Reset to Default", ImVec2(-1, 0)))
        {
            ResetToDefault();
        }

        ImGui::End();
    }
}
