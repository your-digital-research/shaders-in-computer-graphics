#pragma once

#include "imgui.h"

#include "ui/panels/panel.hpp"

namespace scene
{
    class SceneManager;
}

namespace ui::panels
{
    using namespace scene;

    class SceneManagementPanel final : public Panel
    {
    public:
        SceneManagementPanel() = default;
        ~SceneManagementPanel() override = default;

        void Render() override;

        // Setter for scene manager reference
        void SetSceneManager(SceneManager* sceneManager) { m_SceneManager = sceneManager; }

    private:
        SceneManager* m_SceneManager = nullptr;
    };
}
