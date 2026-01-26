#include "ui/panels/performance_panel.hpp"

#include "core/engine.hpp"

namespace ui::panels
{
    void PerformancePanel::Render()
    {
        if (!m_Enabled || !m_Engine) return;

        constexpr float panelWidth = 280.0f;
        constexpr float panelHeight = 85.0f;
        constexpr float padding = 10.0f;

        const ImGuiIO& io = ImGui::GetIO();
        const float yPos = io.DisplaySize.y - panelHeight - padding;

        ImGui::SetNextWindowPos(ImVec2(padding, yPos), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(panelWidth, panelHeight), ImGuiCond_Always);

        ImGui::Begin("Performance", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::Text("FPS: %.1f", io.Framerate);
        ImGui::Text("Frame Time: %.1f ms", 1000.0f / io.Framerate);
        ImGui::Text("Delta Time: %.1f ms", m_Engine->GetCurrentDeltaTime() * 1000.0f);

        ImGui::End();
    }
}
