#pragma once

#include "constants/graphics_constants.hpp"

#include "ui/panels/panel.hpp"

namespace scene
{
    class SceneManager;
}

namespace ui::panels
{
    using namespace scene;

    class EngineSettingsPanel final : public Panel
    {
    public:
        EngineSettingsPanel() = default;
        ~EngineSettingsPanel() override = default;

        void Render() override;

        void SetSceneManager(SceneManager* sceneManager) { m_SceneManager = sceneManager; }

    private:
        int m_BlendMode = 0;
        int m_PolygonMode = 0;

        bool m_Initialized = false;
        bool m_DepthTestEnabled = true;

        float m_ClearColor[3] = {
            constants::graphics::DEFAULT_BACKGROUND_COLOR.r,
            constants::graphics::DEFAULT_BACKGROUND_COLOR.g,
            constants::graphics::DEFAULT_BACKGROUND_COLOR.b
        };

        float m_CameraPosition[3] = {0.0f, 0.0f, 3.0f};
        float m_CameraRotation[3] = {0.0f, 0.0f, 0.0f};

        SceneManager* m_SceneManager = nullptr;

        void Initialize();
        void ResetToDefault();
        void UpdateCameraFromScene();
    };
}
