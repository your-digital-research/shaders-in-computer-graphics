#include "ui/panels/scene_management_panel.hpp"
#include "scene/scene_manager.hpp"

namespace ui::panels
{
    void SceneManagementPanel::Render()
    {
        if (!m_Enabled || !m_SceneManager) return;

        constexpr float panelWidth = 340.0f;
        constexpr float panelHeight = 90.0f;
        constexpr float padding = 10.0f;

        const ImGuiIO& io = ImGui::GetIO();
        const float xPos = io.DisplaySize.x - panelWidth - padding;

        ImGui::SetNextWindowPos(ImVec2(xPos, padding), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

        ImGui::Begin("Scene Management", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        const auto& scenes = m_SceneManager->GetAllScenes();
        const std::string& currentSceneName = m_SceneManager->GetActiveSceneName();

        ImGui::Text("Active Scene:");
        ImGui::SameLine();
        ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "%s", currentSceneName.c_str());

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::Text("Select:");
        ImGui::SameLine();
        ImGui::SetNextItemWidth(170.0f);

        if (ImGui::BeginCombo("##SceneSelect", currentSceneName.c_str()))
        {
            for (const auto& [name, scene] : scenes)
            {
                const bool isSelected = (currentSceneName == name);

                if (ImGui::Selectable(name.c_str(), isSelected))
                {
                    m_SceneManager->SetActiveScene(name);
                }

                if (isSelected)
                {
                    ImGui::SetItemDefaultFocus();
                }
            }

            ImGui::EndCombo();
        }

        ImGui::End();
    }
}
