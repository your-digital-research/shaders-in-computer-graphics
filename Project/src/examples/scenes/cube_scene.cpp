#include "examples/scenes/cube_scene.hpp"

#include <vector>

#include "imgui.h"

#include <glm/gtc/matrix_transform.hpp>

#include "constants/paths.hpp"
#include "utils/math_utils.hpp"

namespace examples
{
    using namespace graphics;

    CubeScene::CubeScene(Camera* camera)
        : Scene(camera)
    {
        SetColorTheme(m_CurrentColorTheme);

        CubeScene::OnCreate();
    }

    CubeScene::~CubeScene()
    {
        CubeScene::OnDestroy();
    }

    void CubeScene::CreateCube()
    {
        if (m_Mesh != nullptr)
        {
            delete m_Mesh;

            m_Mesh = nullptr;
        }

        const float halfSize = m_CubeSize * 0.5f;

        // UV Atlas Layout: [Left][Front][Right][Back][Top][Bottom]
        // Each face occupies 1/6th of the texture width
        constexpr float faceWidth = 1.0f / 6.0f;

        const Vertices vertices = {
            Vertex(glm::vec3(-halfSize, -halfSize, halfSize), m_FrontColor, glm::vec2(faceWidth * 1, 0.0f)),
            Vertex(glm::vec3(halfSize, -halfSize, halfSize), m_FrontColor, glm::vec2(faceWidth * 2, 0.0f)),
            Vertex(glm::vec3(halfSize, halfSize, halfSize), m_FrontColor, glm::vec2(faceWidth * 2, 1.0f)),
            Vertex(glm::vec3(-halfSize, halfSize, halfSize), m_FrontColor, glm::vec2(faceWidth * 1, 1.0f)),

            // Back face - UV range [3/6, 4/6]
            Vertex(glm::vec3(-halfSize, -halfSize, -halfSize), m_BackColor, glm::vec2(faceWidth * 4, 0.0f)),
            Vertex(glm::vec3(-halfSize, halfSize, -halfSize), m_BackColor, glm::vec2(faceWidth * 4, 1.0f)),
            Vertex(glm::vec3(halfSize, halfSize, -halfSize), m_BackColor, glm::vec2(faceWidth * 3, 1.0f)),
            Vertex(glm::vec3(halfSize, -halfSize, -halfSize), m_BackColor, glm::vec2(faceWidth * 3, 0.0f)),

            // Right face - UV range [2/6, 3/6]
            Vertex(glm::vec3(halfSize, -halfSize, halfSize), m_RightColor, glm::vec2(faceWidth * 2, 0.0f)),
            Vertex(glm::vec3(halfSize, -halfSize, -halfSize), m_RightColor, glm::vec2(faceWidth * 3, 0.0f)),
            Vertex(glm::vec3(halfSize, halfSize, -halfSize), m_RightColor, glm::vec2(faceWidth * 3, 1.0f)),
            Vertex(glm::vec3(halfSize, halfSize, halfSize), m_RightColor, glm::vec2(faceWidth * 2, 1.0f)),

            // Left face - UV range [0/6, 1/6]
            Vertex(glm::vec3(-halfSize, -halfSize, -halfSize), m_LeftColor, glm::vec2(faceWidth * 0, 0.0f)),
            Vertex(glm::vec3(-halfSize, -halfSize, halfSize), m_LeftColor, glm::vec2(faceWidth * 1, 0.0f)),
            Vertex(glm::vec3(-halfSize, halfSize, halfSize), m_LeftColor, glm::vec2(faceWidth * 1, 1.0f)),
            Vertex(glm::vec3(-halfSize, halfSize, -halfSize), m_LeftColor, glm::vec2(faceWidth * 0, 1.0f)),

            // Top face - UV range [4/6, 5/6]
            Vertex(glm::vec3(-halfSize, halfSize, halfSize), m_TopColor, glm::vec2(faceWidth * 4, 0.0f)),
            Vertex(glm::vec3(halfSize, halfSize, halfSize), m_TopColor, glm::vec2(faceWidth * 5, 0.0f)),
            Vertex(glm::vec3(halfSize, halfSize, -halfSize), m_TopColor, glm::vec2(faceWidth * 5, 1.0f)),
            Vertex(glm::vec3(-halfSize, halfSize, -halfSize), m_TopColor, glm::vec2(faceWidth * 4, 1.0f)),

            // Bottom face - UV range [5/6, 6/6]
            Vertex(glm::vec3(-halfSize, -halfSize, -halfSize), m_BottomColor, glm::vec2(faceWidth * 5, 1.0f)),
            Vertex(glm::vec3(halfSize, -halfSize, -halfSize), m_BottomColor, glm::vec2(faceWidth * 6, 1.0f)),
            Vertex(glm::vec3(halfSize, -halfSize, halfSize), m_BottomColor, glm::vec2(faceWidth * 6, 0.0f)),
            Vertex(glm::vec3(-halfSize, -halfSize, halfSize), m_BottomColor, glm::vec2(faceWidth * 5, 0.0f))
        };

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

        m_Mesh = new Mesh(vertices, indices);
    }

    void CubeScene::OnCreate()
    {
        CreateCube();

        m_Shader = new Shader(constants::paths::COLORED_VERTEX_SHADER,
                              constants::paths::COLORED_FRAGMENT_SHADER);

        m_Camera->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
    }

    void CubeScene::OnUpdate(const float deltaTime)
    {
        m_RotationAngle += deltaTime * m_RotationSpeed;
        m_RotationAngle = utils::math::WrapAngle360(m_RotationAngle);

        // Normalize the axis before using it for rotation
        if (const float axisLength = glm::length(m_RotationAxis); axisLength > 0.001f)
        {
            const glm::vec3 normalizedAxis = m_RotationAxis / axisLength;

            m_ModelMatrix = glm::rotate(glm::mat4(1.0f), utils::math::ToRadians(m_RotationAngle), normalizedAxis);
        }
        else
        {
            m_ModelMatrix = glm::mat4(1.0f);
        }
    }

    void CubeScene::OnRender()
    {
        if (m_Mesh == nullptr || m_Shader == nullptr) return;

        m_Shader->Bind();

        m_Shader->SetMat4("uModel", m_ModelMatrix);
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        // Set a uniform color when using a basic shader (not used in colored shader)
        // constexpr Color color = Color::GrayAlpha(0.7f, 1.0f);
        // m_Shader->SetVec4("uColor", color.ToVec4());

        m_Mesh->Bind();
        m_Mesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void CubeScene::OnDestroy()
    {
        delete m_Mesh;
        delete m_Shader;

        m_Mesh = nullptr;
        m_Shader = nullptr;
    }

    void CubeScene::SetColorTheme(const CubeColorTheme theme)
    {
        m_CurrentColorTheme = theme;

        switch (theme)
        {
        case CubeColorTheme::Unknown:
            m_FrontColor = Color::White;
            m_BackColor = Color::White;
            m_RightColor = Color::White;
            m_LeftColor = Color::White;
            m_TopColor = Color::White;
            m_BottomColor = Color::White;
            break;

        case CubeColorTheme::PastelDream:
            m_FrontColor = Color::RGBA(1.0f, 0.7f, 0.7f, 1.0f); // Soft coral
            m_BackColor = Color::RGBA(0.7f, 1.0f, 0.8f, 1.0f); // Soft mint
            m_RightColor = Color::RGBA(0.8f, 0.7f, 1.0f, 1.0f); // Soft lavender
            m_LeftColor = Color::RGBA(1.0f, 0.85f, 0.7f, 1.0f); // Soft peach
            m_TopColor = Color::RGBA(0.7f, 0.85f, 1.0f, 1.0f); // Soft sky blue
            m_BottomColor = Color::RGBA(1.0f, 0.75f, 0.85f, 1.0f); // Soft rose
            break;

        case CubeColorTheme::NeonCyberpunk:
            m_FrontColor = Color::RGB(1.0f, 0.0f, 0.8f); // Hot magenta
            m_BackColor = Color::RGB(0.0f, 0.9f, 1.0f); // Cyan
            m_RightColor = Color::RGB(1.0f, 0.2f, 0.0f); // Neon orange
            m_LeftColor = Color::RGB(0.5f, 0.0f, 1.0f); // Electric purple
            m_TopColor = Color::RGB(0.0f, 1.0f, 0.3f); // Neon green
            m_BottomColor = Color::RGB(1.0f, 1.0f, 0.0f); // Electric yellow
            break;

        case CubeColorTheme::OceanDepth:
            m_FrontColor = Color::RGB(0.0f, 0.4f, 0.7f); // Deep blue
            m_BackColor = Color::RGB(0.1f, 0.6f, 0.8f); // Ocean blue
            m_RightColor = Color::RGB(0.2f, 0.8f, 0.9f); // Turquoise
            m_LeftColor = Color::RGB(0.0f, 0.5f, 0.6f); // Teal
            m_TopColor = Color::RGB(0.4f, 0.9f, 1.0f); // Light cyan
            m_BottomColor = Color::RGB(0.0f, 0.2f, 0.4f); // Dark navy
            break;

        case CubeColorTheme::SunsetVibes:
            m_FrontColor = Color::RGB(1.0f, 0.5f, 0.2f); // Orange
            m_BackColor = Color::RGB(1.0f, 0.3f, 0.4f); // Coral pink
            m_RightColor = Color::RGB(1.0f, 0.7f, 0.3f); // Golden
            m_LeftColor = Color::RGB(0.9f, 0.4f, 0.5f); // Rose
            m_TopColor = Color::RGB(1.0f, 0.9f, 0.5f); // Light yellow
            m_BottomColor = Color::RGB(0.6f, 0.2f, 0.3f); // Deep red
            break;

        case CubeColorTheme::ForestNature:
            m_FrontColor = Color::RGB(0.2f, 0.6f, 0.2f); // Forest green
            m_BackColor = Color::RGB(0.4f, 0.7f, 0.3f); // Lime green
            m_RightColor = Color::RGB(0.5f, 0.4f, 0.2f); // Brown
            m_LeftColor = Color::RGB(0.3f, 0.5f, 0.2f); // Moss green
            m_TopColor = Color::RGB(0.6f, 0.8f, 0.4f); // Light green
            m_BottomColor = Color::RGB(0.3f, 0.2f, 0.1f); // Dark brown
            break;

        case CubeColorTheme::RoyalLuxury:
            m_FrontColor = Color::RGB(0.5f, 0.1f, 0.8f); // Royal purple
            m_BackColor = Color::RGB(0.7f, 0.2f, 0.9f); // Violet
            m_RightColor = Color::RGB(1.0f, 0.8f, 0.2f); // Gold
            m_LeftColor = Color::RGB(0.6f, 0.0f, 0.6f); // Magenta
            m_TopColor = Color::RGB(1.0f, 0.9f, 0.5f); // Light gold
            m_BottomColor = Color::RGB(0.3f, 0.0f, 0.5f); // Deep purple
            break;

        case CubeColorTheme::FireAndIce:
            m_FrontColor = Color::RGB(1.0f, 0.2f, 0.0f); // Fire red
            m_BackColor = Color::RGB(0.3f, 0.7f, 1.0f); // Ice blue
            m_RightColor = Color::RGB(1.0f, 0.5f, 0.0f); // Orange flame
            m_LeftColor = Color::RGB(0.5f, 0.9f, 1.0f); // Light ice
            m_TopColor = Color::RGB(1.0f, 0.8f, 0.3f); // Yellow flame
            m_BottomColor = Color::RGB(0.1f, 0.3f, 0.6f); // Deep ice
            break;

        case CubeColorTheme::CandyPop:
            m_FrontColor = Color::RGB(1.0f, 0.4f, 0.7f); // Bubble gum pink
            m_BackColor = Color::RGB(0.5f, 0.9f, 1.0f); // Cotton candy blue
            m_RightColor = Color::RGB(1.0f, 0.6f, 0.9f); // Pink lemonade
            m_LeftColor = Color::RGB(0.7f, 1.0f, 0.5f); // Lime candy
            m_TopColor = Color::RGB(1.0f, 0.9f, 0.4f); // Lemon yellow
            m_BottomColor = Color::RGB(0.9f, 0.5f, 1.0f); // Grape purple
            break;

        case CubeColorTheme::MonochromeGray:
            m_FrontColor = Color::RGB(0.9f, 0.9f, 0.9f); // Light gray
            m_BackColor = Color::RGB(0.7f, 0.7f, 0.7f); // Medium gray
            m_RightColor = Color::RGB(0.5f, 0.5f, 0.5f); // Gray
            m_LeftColor = Color::RGB(0.6f, 0.6f, 0.6f); // Medium-light gray
            m_TopColor = Color::RGB(1.0f, 1.0f, 1.0f); // White
            m_BottomColor = Color::RGB(0.3f, 0.3f, 0.3f); // Dark gray
            break;

        case CubeColorTheme::RainbowSpectrum:
            m_FrontColor = Color::RGB(1.0f, 0.0f, 0.0f); // Red
            m_BackColor = Color::RGB(1.0f, 0.5f, 0.0f); // Orange
            m_RightColor = Color::RGB(1.0f, 1.0f, 0.0f); // Yellow
            m_LeftColor = Color::RGB(0.0f, 1.0f, 0.0f); // Green
            m_TopColor = Color::RGB(0.0f, 0.5f, 1.0f); // Blue
            m_BottomColor = Color::RGB(0.5f, 0.0f, 1.0f); // Purple
            break;
        }

        CreateCube();
    }

    void CubeScene::ResetToDefault()
    {
        m_CubeSize = m_DefaultCubeSize;
        m_RotationSpeed = m_DefaultRotationSpeed;
        m_RotationAxis = m_DefaultRotationAxis;
        m_RotationAngle = 0.0f;

        SetColorTheme(m_DefaultColorTheme);

        m_Camera->SetPosition(m_DefaultCameraPosition);
        m_Camera->SetRotationEuler(m_DefaultCameraRotation);

        CreateCube();
    }

    void CubeScene::RenderSettings()
    {
        constexpr float panelWidth = 340.0f;
        constexpr float panelHeight = 260.0f;
        constexpr float padding = 10.0f;

        const ImGuiIO& io = ImGui::GetIO();
        const float xPos = io.DisplaySize.x - panelWidth - padding;
        const float yPos = io.DisplaySize.y - panelHeight - padding;

        ImGui::SetNextWindowPos(ImVec2(xPos, yPos), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

        ImGui::Begin("Scene Settings", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("Cube Properties");
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Cube Size
        if (ImGui::SliderFloat("Size", &m_CubeSize, 0.1f, 5.0f, "%.2f"))
        {
            CreateCube();
        }

        // Rotation Axis
        ImGui::DragFloat3("Rotation Axis", &m_RotationAxis.x, 0.01f, -1.0f, 1.0f, "%.3f");

        // Rotation Speed
        ImGui::SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 360.0f, "%.1f°/s");

        ImGui::Spacing();

        // Show warning if the axis is near zero
        if (glm::length(m_RotationAxis) < 0.001f)
        {
            ImGui::TextColored(ImVec4(1.0f, 0.5f, 0.0f, 1.0f), "Warning: Zero axis detected!");
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // Color Theme Selection
        const char* themeNames[] = {
            "Pastel Dream",
            "Neon Cyberpunk",
            "Ocean Depth",
            "Sunset Vibes",
            "Forest Nature",
            "Royal Luxury",
            "Fire and Ice",
            "Candy Pop",
            "Monochrome Gray",
            "Rainbow Spectrum"
        };

        constexpr CubeColorTheme themes[] = {
            CubeColorTheme::PastelDream,
            CubeColorTheme::NeonCyberpunk,
            CubeColorTheme::OceanDepth,
            CubeColorTheme::SunsetVibes,
            CubeColorTheme::ForestNature,
            CubeColorTheme::RoyalLuxury,
            CubeColorTheme::FireAndIce,
            CubeColorTheme::CandyPop,
            CubeColorTheme::MonochromeGray,
            CubeColorTheme::RainbowSpectrum
        };

        int currentThemeIndex = 0;
        for (int i = 0; i < 10; i++)
        {
            if (m_CurrentColorTheme == themes[i])
            {
                currentThemeIndex = i;

                break;
            }
        }

        if (ImGui::Combo("Color Theme", &currentThemeIndex, themeNames, IM_ARRAYSIZE(themeNames)))
        {
            SetColorTheme(themes[currentThemeIndex]);
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
