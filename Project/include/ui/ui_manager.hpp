#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "platform/window.hpp"

#include "ui/panels/active_scene_settings_panel.hpp"
#include "ui/panels/engine_settings_panel.hpp"
#include "ui/panels/performance_panel.hpp"
#include "ui/panels/scene_management_panel.hpp"

namespace core
{
    class Engine;
}

namespace ui
{
    using namespace core;
    using namespace platform;
    using namespace panels;

    class UIManager
    {
    public:
        explicit UIManager(const Window* window);
        ~UIManager();

        void BeginFrame() const;
        void EndFrame() const;

        void InitializePanels(Engine* engine) const;
        void RenderUI() const;

        void SetEnabled(const bool enabled) { m_Enabled = enabled; }
        [[nodiscard]] bool IsEnabled() const { return m_Enabled; }

    private:
        bool m_Enabled;

        mutable PerformancePanel m_PerformancePanel;
        mutable EngineSettingsPanel m_EngineSettingsPanel;
        mutable SceneManagementPanel m_SceneManagementPanel;
        mutable ActiveSceneSettingsPanel m_ActiveSceneSettingsPanel;
    };
}
