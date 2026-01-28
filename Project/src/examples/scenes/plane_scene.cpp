#include "examples/scenes/plane_scene.hpp"

#include <vector>

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "constants/paths.hpp"
#include "utils/math_utils.hpp"

namespace examples
{
    PlaneScene::PlaneScene(Camera* camera)
        : Scene(camera)
    {
        SetColorTheme(m_CurrentColorTheme);

        PlaneScene::OnCreate();
    }

    PlaneScene::~PlaneScene()
    {
        PlaneScene::OnDestroy();
    }

    void PlaneScene::CreatePlane(const int gridSize, const float planeSize)
    {
        if (m_Mesh != nullptr)
        {
            delete m_Mesh;

            m_Mesh = nullptr;
        }

        Vertices vertices;
        VertexIndices indices;

        const float stepSize = planeSize / static_cast<float>(gridSize);
        const float halfSize = planeSize * 0.5f;

        // Generate grid vertices
        for (int z = 0; z <= gridSize; ++z)
        {
            for (int x = 0; x <= gridSize; ++x)
            {
                const float xPos = static_cast<float>(x) * stepSize - halfSize;
                const float zPos = static_cast<float>(z) * stepSize - halfSize;
                const float u = static_cast<float>(x) / static_cast<float>(gridSize);
                const float v = static_cast<float>(z) / static_cast<float>(gridSize);

                vertices.emplace_back(glm::vec3(xPos, 0.0f, zPos), Color::White, glm::vec2(u, v));
            }
        }

        // Generate triangle indices
        for (int z = 0; z < gridSize; ++z)
        {
            for (int x = 0; x < gridSize; ++x)
            {
                const int topLeft = z * (gridSize + 1) + x;
                const int topRight = topLeft + 1;
                const int bottomLeft = (z + 1) * (gridSize + 1) + x;
                const int bottomRight = bottomLeft + 1;

                indices.push_back(topLeft);
                indices.push_back(bottomLeft);
                indices.push_back(topRight);

                // Second triangle
                indices.push_back(topRight);
                indices.push_back(bottomLeft);
                indices.push_back(bottomRight);
            }
        }

        m_Mesh = new Mesh(vertices, indices);
    }

    void PlaneScene::OnCreate()
    {
        CreatePlane(m_GridSize, m_PlaneSize);

        m_Shader = new Shader(constants::paths::WAVE_VERTEX_SHADER,
                              constants::paths::WAVE_FRAGMENT_SHADER);

        m_Camera->SetPosition(glm::vec3(0.0f, 7.5f, 8.25f));
        m_Camera->SetRotationEuler(glm::vec3(-45.0f, 0.0f, 0.0f));

        // Calculate plane radius: half diagonal from center to corner
        m_PlaneRadius = m_PlaneSize * (constants::math::SQRT_2 / 2.0f);

        // Calculate wave frequency to fit m_WaveCount wavelengths in the radius
        if (utils::math::FloatEqual(m_WaveFrequency, constants::math::PI))
        {
            m_WaveFrequency = (static_cast<float>(m_WaveCount) * constants::math::TWO_PI) / m_PlaneRadius;
        }

        m_DefaultWaveFrequency = m_WaveFrequency;
    }

    void PlaneScene::OnUpdate(const float deltaTime)
    {
        m_Time += deltaTime * m_WaveSpeed;
    }

    void PlaneScene::OnRender()
    {
        if (m_Mesh == nullptr || m_Shader == nullptr) return;

        m_Shader->Bind();

        m_Shader->SetMat4("uModel", m_ModelMatrix);
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        m_Shader->SetFloat("uTime", m_Time);
        m_Shader->SetFloat("uWaveAmplitude", m_WaveAmplitude);
        m_Shader->SetFloat("uWaveFrequency", m_WaveFrequency);
        m_Shader->SetFloat("uOpacityFadeStart", m_OpacityFadeStart);
        m_Shader->SetFloat("uPlaneRadius", m_PlaneRadius);

        m_Shader->SetVec4("uCenterColor", m_CenterColor.ToVec4());
        m_Shader->SetVec4("uEdgeColor", m_EdgeColor.ToVec4());
        m_Shader->SetVec4("uWavePeakColor", m_WavePeakColor.ToVec4());
        m_Shader->SetVec4("uWaveTroughColor", m_WaveTroughColor.ToVec4());

        m_Mesh->Bind();
        m_Mesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void PlaneScene::OnDestroy()
    {
        delete m_Mesh;
        delete m_Shader;

        m_Mesh = nullptr;
        m_Shader = nullptr;
    }

    void PlaneScene::SetColorTheme(const PlaneColorTheme theme)
    {
        m_CurrentColorTheme = theme;

        switch (theme)
        {
        case PlaneColorTheme::Unknown:
            m_CenterColor = Color::White;
            m_EdgeColor = Color::White;
            m_WavePeakColor = Color::White;
            m_WaveTroughColor = Color::White;
            break;

        case PlaneColorTheme::AuroraSunset:
            m_CenterColor = Color::RGB(0.6f, 0.2f, 0.8f); // Deep purple
            m_EdgeColor = Color::RGB(1.0f, 0.6f, 0.3f); // Warm orange
            m_WavePeakColor = Color::RGB(1.0f, 0.9f, 0.4f); // Golden yellow
            m_WaveTroughColor = Color::RGB(0.4f, 0.15f, 0.6f); // Dark purple
            break;

        case PlaneColorTheme::NeonCyberpunk:
            m_CenterColor = Color::RGB(1.0f, 0.0f, 0.8f); // Hot magenta
            m_EdgeColor = Color::RGB(0.0f, 0.9f, 1.0f); // Bright cyan
            m_WavePeakColor = Color::RGB(1.0f, 1.0f, 1.0f); // Pure white
            m_WaveTroughColor = Color::RGB(0.4f, 0.0f, 0.6f); // Deep magenta
            break;

        case PlaneColorTheme::OceanDepth:
            m_CenterColor = Color::RGB(0.0f, 0.3f, 0.6f); // Deep ocean blue
            m_EdgeColor = Color::RGB(0.2f, 0.9f, 0.9f); // Bright turquoise
            m_WavePeakColor = Color::RGB(0.7f, 1.0f, 1.0f); // Light aqua foam
            m_WaveTroughColor = Color::RGB(0.0f, 0.2f, 0.4f); // Dark navy
            break;

        case PlaneColorTheme::FireLava:
            m_CenterColor = Color::RGB(0.8f, 0.1f, 0.0f); // Deep red
            m_EdgeColor = Color::RGB(1.0f, 0.8f, 0.0f); // Bright yellow
            m_WavePeakColor = Color::RGB(1.0f, 1.0f, 0.8f); // White-hot
            m_WaveTroughColor = Color::RGB(0.5f, 0.0f, 0.0f); // Dark crimson
            break;

        case PlaneColorTheme::MintRose:
            m_CenterColor = Color::RGB(1.0f, 0.4f, 0.7f); // Soft rose pink
            m_EdgeColor = Color::RGB(0.4f, 1.0f, 0.8f); // Mint green
            m_WavePeakColor = Color::RGB(1.0f, 0.95f, 0.85f); // Cream white
            m_WaveTroughColor = Color::RGB(0.7f, 0.2f, 0.5f); // Deep rose
            break;

        case PlaneColorTheme::ToxicGreen:
            m_CenterColor = Color::RGB(0.2f, 0.8f, 0.1f); // Bright lime
            m_EdgeColor = Color::RGB(0.8f, 1.0f, 0.0f); // Neon yellow-green
            m_WavePeakColor = Color::RGB(0.9f, 1.0f, 0.7f); // Light lime
            m_WaveTroughColor = Color::RGB(0.1f, 0.4f, 0.0f); // Dark forest green
            break;

        case PlaneColorTheme::RoyalPurpleGold:
            m_CenterColor = Color::RGB(0.5f, 0.1f, 0.8f); // Royal purple
            m_EdgeColor = Color::RGB(1.0f, 0.85f, 0.2f); // Rich gold
            m_WavePeakColor = Color::RGB(1.0f, 0.95f, 0.6f); // Light gold
            m_WaveTroughColor = Color::RGB(0.3f, 0.05f, 0.5f); // Deep violet
            break;

        case PlaneColorTheme::CottonCandy:
            m_CenterColor = Color::RGB(1.0f, 0.6f, 0.9f); // Pink
            m_EdgeColor = Color::RGB(0.6f, 0.8f, 1.0f); // Baby blue
            m_WavePeakColor = Color::RGB(1.0f, 0.95f, 1.0f); // Almost white
            m_WaveTroughColor = Color::RGB(0.8f, 0.4f, 0.7f); // Mauve
            break;

        case PlaneColorTheme::ElectricStorm:
            m_CenterColor = Color::RGB(0.1f, 0.1f, 0.9f); // Electric blue
            m_EdgeColor = Color::RGB(0.9f, 0.9f, 1.0f); // Bright white-blue
            m_WavePeakColor = Color::RGB(1.0f, 1.0f, 0.7f); // Lightning yellow
            m_WaveTroughColor = Color::RGB(0.05f, 0.0f, 0.5f); // Deep indigo
            break;

        case PlaneColorTheme::PeachSunset:
            m_CenterColor = Color::RGB(1.0f, 0.5f, 0.3f); // Coral peach
            m_EdgeColor = Color::RGB(1.0f, 0.9f, 0.5f); // Soft yellow
            m_WavePeakColor = Color::RGB(1.0f, 0.95f, 0.8f); // Cream
            m_WaveTroughColor = Color::RGB(0.8f, 0.3f, 0.2f); // Deep orange
            break;

        case PlaneColorTheme::MatrixGreen:
            m_CenterColor = Color::RGB(0.0f, 0.8f, 0.3f); // Matrix green
            m_EdgeColor = Color::RGB(0.5f, 1.0f, 0.6f); // Light green
            m_WavePeakColor = Color::RGB(0.8f, 1.0f, 0.9f); // Mint white
            m_WaveTroughColor = Color::RGB(0.0f, 0.4f, 0.1f); // Dark emerald
            break;
        }
    }

    void PlaneScene::SetWaveSpeed(const float speed)
    {
        m_WaveSpeed = speed;
    }

    void PlaneScene::SetWaveAmplitude(const float amplitude)
    {
        m_WaveAmplitude = glm::max(0.0f, amplitude);
    }

    void PlaneScene::SetWaveFrequency(const float frequency)
    {
        m_WaveFrequency = glm::max(0.1f, frequency);
    }

    void PlaneScene::SetOpacityFadeStart(const float opacityStart)
    {
        m_OpacityFadeStart = glm::clamp(opacityStart, 0.0f, 1.0f);
    }

    void PlaneScene::SetGridSize(const int gridSize)
    {
        m_GridSize = glm::max(2, gridSize);

        CreatePlane(m_GridSize, m_PlaneSize);
    }

    void PlaneScene::SetPlaneSize(const float planeSize)
    {
        m_PlaneSize = glm::max(1.0f, planeSize);
        m_PlaneRadius = m_PlaneSize * (constants::math::SQRT_2 / 2.0f);

        CreatePlane(m_GridSize, m_PlaneSize);
    }

    void PlaneScene::SetCenterColor(const Color& color)
    {
        m_CenterColor = color;
        m_CurrentColorTheme = PlaneColorTheme::Unknown;
    }

    void PlaneScene::SetEdgeColor(const Color& color)
    {
        m_EdgeColor = color;
        m_CurrentColorTheme = PlaneColorTheme::Unknown;
    }

    void PlaneScene::SetWavePeakColor(const Color& color)
    {
        m_WavePeakColor = color;
        m_CurrentColorTheme = PlaneColorTheme::Unknown;
    }

    void PlaneScene::SetWaveTroughColor(const Color& color)
    {
        m_WaveTroughColor = color;
        m_CurrentColorTheme = PlaneColorTheme::Unknown;
    }

    void PlaneScene::ResetToDefault()
    {
        m_WaveSpeed = m_DefaultWaveSpeed;
        m_WaveAmplitude = m_DefaultWaveAmplitude;
        m_WaveFrequency = m_DefaultWaveFrequency;
        m_OpacityFadeStart = m_DefaultOpacityFadeStart;
        m_GridSize = m_DefaultGridSize;
        m_PlaneSize = m_DefaultPlaneSize;
        m_Time = 0.0f;

        m_PlaneRadius = m_PlaneSize * (constants::math::SQRT_2 / 2.0f);

        SetColorTheme(m_DefaultColorTheme);

        m_Camera->SetPosition(m_DefaultCameraPosition);
        m_Camera->SetRotationEuler(m_DefaultCameraRotation);

        CreatePlane(m_GridSize, m_PlaneSize);
    }

    void PlaneScene::RenderSettings()
    {
        constexpr float panelWidth = 340.0f;
        constexpr float panelHeight = 500.0f;
        constexpr float padding = 10.0f;

        const ImGuiIO& io = ImGui::GetIO();
        const float xPos = io.DisplaySize.x - panelWidth - padding;
        const float yPos = io.DisplaySize.y - panelHeight - padding;

        ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

        ImGui::Begin("Scene Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Plane Properties");
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Grid Size
        int gridSize = m_GridSize;
        if (ImGui::SliderInt("Grid Size", &gridSize, 2, 256))
        {
            SetGridSize(gridSize);
        }

        // Plane Size
        float planeSize = m_PlaneSize;
        if (ImGui::SliderFloat("Plane Size", &planeSize, 1.0f, 20.0f, "%.2f"))
        {
            SetPlaneSize(planeSize);
        }

        ImGui::Spacing();

        // Plane Radius (read-only display)
        ImGui::Text("Plane Radius: %.2f", m_PlaneRadius);

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Wave Properties");
        ImGui::Spacing();

        // Wave Speed
        float waveSpeed = m_WaveSpeed;
        if (ImGui::SliderFloat("Wave Speed", &waveSpeed, 0.0f, 20.0f, "%.2f"))
        {
            SetWaveSpeed(waveSpeed);
        }

        // Wave Amplitude
        float waveAmplitude = m_WaveAmplitude;
        if (ImGui::SliderFloat("Amplitude", &waveAmplitude, 0.0f, 2.0f, "%.3f"))
        {
            SetWaveAmplitude(waveAmplitude);
        }

        // Wave Frequency
        float waveFrequency = m_WaveFrequency;
        if (ImGui::SliderFloat("Frequency", &waveFrequency, 0.1f, 20.0f, "%.3f"))
        {
            SetWaveFrequency(waveFrequency);
        }

        // Opacity Fade Start
        float opacityFadeStart = m_OpacityFadeStart;
        if (ImGui::SliderFloat("Opacity Start", &opacityFadeStart, 0.0f, 1.0f, "%.3f"))
        {
            SetOpacityFadeStart(opacityFadeStart);
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Color Theme Selection
        ImGui::Text("Color Theme");
        ImGui::Spacing();

        const char* themeNames[] = {
            "Custom",
            "Aurora Sunset",
            "Neon Cyberpunk",
            "Ocean Depth",
            "Fire Lava",
            "Mint Rose",
            "Toxic Green",
            "Royal Purple Gold",
            "Cotton Candy",
            "Electric Storm",
            "Peach Sunset",
            "Matrix Green"
        };

        constexpr PlaneColorTheme themes[] = {
            PlaneColorTheme::Unknown,
            PlaneColorTheme::AuroraSunset,
            PlaneColorTheme::NeonCyberpunk,
            PlaneColorTheme::OceanDepth,
            PlaneColorTheme::FireLava,
            PlaneColorTheme::MintRose,
            PlaneColorTheme::ToxicGreen,
            PlaneColorTheme::RoyalPurpleGold,
            PlaneColorTheme::CottonCandy,
            PlaneColorTheme::ElectricStorm,
            PlaneColorTheme::PeachSunset,
            PlaneColorTheme::MatrixGreen
        };

        int currentThemeIndex = 0;
        for (int i = 0; i < 12; i++)
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

        // Center Color
        float centerColor[3] = {m_CenterColor.r, m_CenterColor.g, m_CenterColor.b};
        if (ImGui::ColorEdit3("Center", centerColor))
        {
            SetCenterColor(Color::RGB(centerColor[0], centerColor[1], centerColor[2]));
        }

        // Edge Color
        float edgeColor[3] = {m_EdgeColor.r, m_EdgeColor.g, m_EdgeColor.b};
        if (ImGui::ColorEdit3("Edge", edgeColor))
        {
            SetEdgeColor(Color::RGB(edgeColor[0], edgeColor[1], edgeColor[2]));
        }

        // Wave Peak Color
        float wavePeakColor[3] = {m_WavePeakColor.r, m_WavePeakColor.g, m_WavePeakColor.b};
        if (ImGui::ColorEdit3("Peak", wavePeakColor))
        {
            SetWavePeakColor(Color::RGB(wavePeakColor[0], wavePeakColor[1], wavePeakColor[2]));
        }

        // Wave Trough Color
        float waveTroughColor[3] = {m_WaveTroughColor.r, m_WaveTroughColor.g, m_WaveTroughColor.b};
        if (ImGui::ColorEdit3("Trough", waveTroughColor))
        {
            SetWaveTroughColor(Color::RGB(waveTroughColor[0], waveTroughColor[1], waveTroughColor[2]));
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
