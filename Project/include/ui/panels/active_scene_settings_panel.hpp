#pragma once

#include "ui/panels/panel.hpp"

namespace scene
{
    class SceneManager;
}

namespace ui::panels
{
    using namespace scene;

    class ActiveSceneSettingsPanel final : public Panel
    {
    public:
        ActiveSceneSettingsPanel() = default;
        ~ActiveSceneSettingsPanel() override = default;

        void Render() override;

        void SetSceneManager(SceneManager* sceneManager) { m_SceneManager = sceneManager; }

    private:
        SceneManager* m_SceneManager = nullptr;
    };
}
