#include "ui/panels/active_scene_settings_panel.hpp"
#include "scene/scene_manager.hpp"
#include "scene/scene.hpp"

namespace ui::panels
{
    void ActiveSceneSettingsPanel::Render()
    {
        if (!m_Enabled || !m_SceneManager) return;

        Scene* activeScene = m_SceneManager->GetActiveScene();

        if (!activeScene) return;

        activeScene->RenderSettings();
    }
}