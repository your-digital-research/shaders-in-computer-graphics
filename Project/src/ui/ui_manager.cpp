#include "ui/ui_manager.hpp"

#include <iostream>
#include <stdexcept>

#include "core/engine.hpp"
#include "scene/scene_manager.hpp"

namespace ui
{
    using namespace core;
    using namespace panels;

    UIManager::UIManager(const Window* window)
        : m_Enabled(true)
    {
        if (!window)
        {
            throw std::invalid_argument("Window pointer cannot be null!");
        }

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();

        if (!ImGui::CreateContext())
        {
            throw std::runtime_error("Failed to create ImGui context!");
        }

        ImGuiIO& io = ImGui::GetIO();

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        // Setup Dear ImGui style
        ImGui::StyleColorsClassic();

        // Setup Platform / Renderer backends
        if (!ImGui_ImplOpenGL3_Init("#version 330"))
        {
            ImGui::DestroyContext();

            throw std::runtime_error("Failed to initialize ImGui OpenGL3 backend!");
        }

        if (!ImGui_ImplGlfw_InitForOpenGL(window->GetNativeWindow(), true))
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui::DestroyContext();

            throw std::runtime_error("Failed to initialize ImGui GLFW backend!");
        }
    }

    UIManager::~UIManager()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();

        ImGui::DestroyContext();
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

    void UIManager::InitializePanels(Engine* engine) const
    {
        const auto sceneManager = &engine->GetSceneManager();

        m_PerformancePanel.SetEngine(engine);
        m_EngineSettingsPanel.SetSceneManager(sceneManager);
        m_SceneManagementPanel.SetSceneManager(sceneManager);
        m_ActiveSceneSettingsPanel.SetSceneManager(sceneManager);
    }

    void UIManager::RenderUI() const
    {
        if (!m_Enabled) return;

        m_PerformancePanel.Render();
        m_EngineSettingsPanel.Render();
        m_SceneManagementPanel.Render();
        m_ActiveSceneSettingsPanel.Render();
    }
}
