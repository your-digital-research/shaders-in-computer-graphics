#include <iostream>

#include "core/engine.hpp"
#include "ui/ui_manager.hpp"
#include "scene/scene_manager.hpp"

namespace ui
{
    using namespace std;
    using namespace core;
    using namespace panels;

    UIManager::UIManager(const Window* window)
        : m_Enabled(true)
    {
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();

        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        // Setup Dear ImGui style
        ImGui::StyleColorsClassic();

        // Setup Platform / Renderer backends
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui_ImplGlfw_InitForOpenGL(window->GetNativeWindow(), true);

        // cout << "UIManager initialized successfully!" << endl;
    }

    UIManager::~UIManager()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        ImGui::DestroyContext();

        // cout << "UIManager shutdown successfully!" << endl;
    }

    void UIManager::BeginFrame() const
    {
        if (!m_Enabled) return;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();
    }

    void UIManager::EndFrame() const
    {
        if (!m_Enabled) return;

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UIManager::SetupPanels(Engine* engine) const
    {
        const auto sceneManager = &engine->GetSceneManager();

        m_PerformancePanel.SetEngine(engine);
        m_SceneManagementPanel.SetSceneManager(sceneManager);
    }

    void UIManager::RenderUI() const
    {
        if (!m_Enabled) return;

        m_PerformancePanel.Render();
        m_EngineSettingsPanel.Render();
        m_SceneManagementPanel.Render();
    }
}
