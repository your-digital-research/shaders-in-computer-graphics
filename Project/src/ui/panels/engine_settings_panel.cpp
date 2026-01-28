#include "ui/panels/engine_settings_panel.hpp"

#include "constants/graphics_constants.hpp"
#include "graphics/color.hpp"
#include "graphics/renderer.hpp"
#include "scene/scene.hpp"
#include "scene/scene_manager.hpp"

namespace ui::panels
{
    using namespace graphics;
    using namespace view;

    void EngineSettingsPanel::Render()
    {
        if (!m_Enabled) return;

        constexpr float panelWidth = 280.0f;
        constexpr float panelHeight = 420.0f;
        constexpr float padding = 10.0f;

        ImGui::SetNextWindowPos(ImVec2(padding, padding), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);
        ImGui::Begin("Engine / Renderer", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        if (!m_Initialized)
        {
            Initialize();
        }

        ImGui::Text("OpenGL State");
        ImGui::Spacing();

        if (ImGui::Checkbox("Depth Test", &m_DepthTestEnabled))
        {
            if (m_DepthTestEnabled)
            {
                Renderer::EnableDepthTest();
            }
            else
            {
                Renderer::DisableDepthTest();
            }
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        const char* blendModes[] = { "None", "Alpha", "Additive", "Multiply" };
        const char* currentBlendMode = blendModes[m_BlendMode];

        ImGui::SetNextItemWidth(150.0f);

        if (ImGui::BeginCombo("Blend Mode", currentBlendMode))
        {
            for (int i = 0; i < 4; i++)
            {
                const bool isSelected = (m_BlendMode == i);

                if (ImGui::Selectable(blendModes[i], isSelected))
                {
                    m_BlendMode = i;

                    if (i == 0)
                    {
                        Renderer::DisableBlending();
                    }
                    else if (i == 1)
                    {
                        Renderer::EnableBlending();
                        Renderer::SetBlendModeAlpha();
                    }
                    else if (i == 2)
                    {
                        Renderer::EnableBlending();
                        Renderer::SetBlendModeAdditive();
                    }
                    else if (i == 3)
                    {
                        Renderer::EnableBlending();
                        Renderer::SetBlendModeMultiply();
                    }
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }
            ImGui::EndCombo();
        }

        ImGui::Spacing();

        const char* polygonModes[] = { "Fill", "Wireframe", "Point" };
        const char* currentPolygonMode = polygonModes[m_PolygonMode];

        ImGui::SetNextItemWidth(150.0f);

        if (ImGui::BeginCombo("Polygon Mode", currentPolygonMode))
        {
            for (int i = 0; i < 3; i++)
            {
                const bool isSelected = (m_PolygonMode == i);

                if (ImGui::Selectable(polygonModes[i], isSelected))
                {
                    m_PolygonMode = i;

                    if (i == 0)
                    {
                        Renderer::SetPolygonModeFill();
                    }
                    else if (i == 1)
                    {
                        Renderer::SetPolygonModeWireframe();
                    }
                    else if (i == 2)
                    {
                        Renderer::SetPolygonModePoint();
                    }
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Background Color");
        ImGui::Spacing();

        if (ImGui::ColorEdit3("##BackgroundColor", m_ClearColor))
        {
            Renderer::SetBackgroundColor(Color::RGB(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2]));
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Camera");
        ImGui::Spacing();

        ImGui::SetNextItemWidth(175.0f);

        if (ImGui::DragFloat3("Position##Camera", m_CameraPosition, 0.05f, -10.0f, 10.0f, "%.2f"))
        {
            if (m_SceneManager && m_SceneManager->GetActiveScene())
            {
                m_SceneManager->GetActiveScene()->SetCameraPosition(glm::vec3(m_CameraPosition[0], m_CameraPosition[1], m_CameraPosition[2]));
            }
        }

        ImGui::SetNextItemWidth(175.0f);

        if (ImGui::DragFloat3("Rotation##Camera", m_CameraRotation, 1.0f, -180.0f, 180.0f, "%.1f"))
        {
            if (m_SceneManager && m_SceneManager->GetActiveScene())
            {
                m_SceneManager->GetActiveScene()->SetCameraRotation(glm::vec3(m_CameraRotation[0], m_CameraRotation[1], m_CameraRotation[2]));
            }
        }

        ImGui::SetNextItemWidth(175.0f);

        const char* projectionTypes[] = { "Perspective", "Orthographic" };

        if (const char* currentProjectionType = projectionTypes[m_CameraProjectionType]; ImGui::BeginCombo("Projection", currentProjectionType))
        {
            for (int i = 0; i < 2; i++)
            {
                const bool isSelected = (m_CameraProjectionType == i);

                if (ImGui::Selectable(projectionTypes[i], isSelected))
                {
                    m_CameraProjectionType = i;

                    if (m_SceneManager && m_SceneManager->GetActiveScene())
                    {
                        m_SceneManager->GetActiveScene()->SetCameraProjectionType(
                            i == 0 ? ProjectionType::Perspective : ProjectionType::Orthographic
                        );
                    }
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        ImGui::SetNextItemWidth(175.0f);

        // FOV control (only for perspective)
        if (m_CameraProjectionType == 0)
        {
            if (ImGui::DragFloat("FOV##Camera", &m_CameraFov, 0.5f, 1.0f, 120.0f, "%.1f"))
            {
                if (m_SceneManager && m_SceneManager->GetActiveScene())
                {
                    m_SceneManager->GetActiveScene()->SetCameraFov(m_CameraFov);
                }
            }
        }

        ImGui::SetNextItemWidth(175.0f);

        if (ImGui::DragFloat("Near Plane##Camera", &m_CameraNearPlane, 0.1f, 0.01f, m_CameraFarPlane - 0.1f, "%.2f"))
        {
            if (m_SceneManager && m_SceneManager->GetActiveScene())
            {
                m_SceneManager->GetActiveScene()->SetCameraNearPlane(m_CameraNearPlane);
            }
        }

        ImGui::SetNextItemWidth(175.0f);

        if (ImGui::DragFloat("Far Plane##Camera", &m_CameraFarPlane, 0.1f, m_CameraNearPlane + 0.1f, 1000.0f, "%.1f"))
        {
            if (m_SceneManager && m_SceneManager->GetActiveScene())
            {
                m_SceneManager->GetActiveScene()->SetCameraFarPlane(m_CameraFarPlane);
            }
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        constexpr float buttonHeight = 30.0f;
        if (const float availableHeight = ImGui::GetContentRegionAvail().y; availableHeight > buttonHeight)
        {
            ImGui::Dummy(ImVec2(0.0f, availableHeight - buttonHeight));
        }

        // ImGui::Separator();

        if (ImGui::Button("Reset to Default", ImVec2(-1, 0)))
        {
            ResetToDefault();
        }

        UpdateCameraFromScene();

        ImGui::End();
    }

    void EngineSettingsPanel::Initialize()
    {
        // Query the current OpenGL depth test state
        m_DepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);

        // Query the current OpenGL blending state
        if (const bool isBlendingEnabled = glIsEnabled(GL_BLEND); !isBlendingEnabled)
        {
            m_BlendMode = 0; // None
        }
        else
        {
            m_BlendMode = 1; // Alpha (default)
        }

        // Query current OpenGL polygon mode
        GLint modes[2];
        glGetIntegerv(GL_POLYGON_MODE, modes);

        if (modes[0] == GL_FILL)
        {
            m_PolygonMode = 0; // Fill
        }
        else if (modes[0] == GL_LINE)
        {
            m_PolygonMode = 1; // Wireframe
        }
        else if (modes[0] == GL_POINT)
        {
            m_PolygonMode = 2; // Point
        }

        m_Initialized = true;
    }

    void EngineSettingsPanel::ResetToDefault()
    {
        constexpr auto defaultColor = constants::graphics::DEFAULT_BACKGROUND_COLOR;
        m_ClearColor[0] = defaultColor.r;
        m_ClearColor[1] = defaultColor.g;
        m_ClearColor[2] = defaultColor.b;
        Renderer::SetBackgroundColor(defaultColor);

        m_DepthTestEnabled = true;
        Renderer::EnableDepthTest();

        m_BlendMode = 0;
        Renderer::DisableBlending();

        m_PolygonMode = 0;
        Renderer::SetPolygonModeFill();

        if (m_SceneManager && m_SceneManager->GetActiveScene())
        {
            const glm::vec3 position = m_SceneManager->GetActiveScene()->GetDefaultCameraPosition();
            m_SceneManager->GetActiveScene()->SetCameraPosition(position);
            m_CameraPosition[0] = position.x;
            m_CameraPosition[1] = position.y;
            m_CameraPosition[2] = position.z;

            const glm::vec3 rotation = m_SceneManager->GetActiveScene()->GetDefaultCameraRotation();
            m_SceneManager->GetActiveScene()->SetCameraRotation(rotation);
            m_CameraRotation[0] = rotation.x;
            m_CameraRotation[1] = rotation.y;
            m_CameraRotation[2] = rotation.z;

            // Reset camera projection settings
            m_CameraProjectionType = 0; // Perspective
            m_SceneManager->GetActiveScene()->SetCameraProjectionType(ProjectionType::Perspective);

            m_CameraFov = constants::graphics::DEFAULT_FOV;
            m_SceneManager->GetActiveScene()->SetCameraFov(m_CameraFov);

            m_CameraNearPlane = constants::graphics::DEFAULT_NEAR_PLANE;
            m_SceneManager->GetActiveScene()->SetCameraNearPlane(m_CameraNearPlane);

            m_CameraFarPlane = constants::graphics::DEFAULT_FAR_PLANE;
            m_SceneManager->GetActiveScene()->SetCameraFarPlane(m_CameraFarPlane);
        }
    }

    void EngineSettingsPanel::UpdateCameraFromScene()
    {
        if (!m_SceneManager || !m_SceneManager->GetActiveScene()) return;

        const glm::vec3 position = m_SceneManager->GetActiveScene()->GetCameraPosition();
        m_CameraPosition[0] = position.x;
        m_CameraPosition[1] = position.y;
        m_CameraPosition[2] = position.z;

        const glm::vec3 rotation = m_SceneManager->GetActiveScene()->GetCameraRotation();
        m_CameraRotation[0] = rotation.x;
        m_CameraRotation[1] = rotation.y;
        m_CameraRotation[2] = rotation.z;

        const ProjectionType projType = m_SceneManager->GetActiveScene()->GetCameraProjectionType();
        m_CameraProjectionType = (projType == ProjectionType::Perspective) ? 0 : 1;

        m_CameraFov = m_SceneManager->GetActiveScene()->GetCameraFov();
        m_CameraNearPlane = m_SceneManager->GetActiveScene()->GetCameraNearPlane();
        m_CameraFarPlane = m_SceneManager->GetActiveScene()->GetCameraFarPlane();
    }
}
