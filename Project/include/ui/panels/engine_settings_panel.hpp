#pragma once

#include "imgui.h"

#include "constants/graphics_constants.hpp"

#include "ui/panels/panel.hpp"

namespace ui::panels
{
    class EngineSettingsPanel final : public Panel
    {
    public:
        EngineSettingsPanel() = default;
        ~EngineSettingsPanel() override = default;

        void Render() override;

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

        void Initialize();
        void ResetToDefault();
    };
}
