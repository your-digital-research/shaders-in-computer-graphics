#include "ui/panels/engine_settings_panel.hpp"
#include "graphics/renderer.hpp"
#include "graphics/color.hpp"

namespace ui::panels
{
    using namespace graphics;

    void EngineSettingsPanel::Render()
    {
        if (!m_Enabled) return;

        constexpr float panelWidth = 280.0f;
        constexpr float panelHeight = 360.0f;
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

        ImGui::Text("Blend Mode:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120.0f);

        if (ImGui::BeginCombo("##BlendMode", currentBlendMode))
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

        ImGui::Text("Polygon Mode:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(120.0f);

        if (ImGui::BeginCombo("##PolygonMode", currentPolygonMode))
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

        constexpr float buttonHeight = 30.0f;

        if (const float availableHeight = ImGui::GetContentRegionAvail().y; availableHeight > buttonHeight)
        {
            ImGui::Dummy(ImVec2(0.0f, availableHeight - buttonHeight));
        }

        ImGui::Separator();

        if (ImGui::Button("Reset to Default", ImVec2(-1, 0)))
        {
            ResetToDefault();
        }

        ImGui::End();
    }

    void EngineSettingsPanel::Initialize()
    {
        m_DepthTestEnabled = glIsEnabled(GL_DEPTH_TEST);

        if (const bool isBlendingEnabled = glIsEnabled(GL_BLEND); !isBlendingEnabled)
        {
            m_BlendMode = 0;
        }
        else
        {
            m_BlendMode = 1;
        }

        GLint modes[2];
        glGetIntegerv(GL_POLYGON_MODE, modes);

        if (modes[0] == GL_FILL)
        {
            m_PolygonMode = 0;
        }
        else if (modes[0] == GL_LINE)
        {
            m_PolygonMode = 1;
        }
        else if (modes[0] == GL_POINT)
        {
            m_PolygonMode = 2;
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
    }
}
