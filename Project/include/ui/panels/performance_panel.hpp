#pragma once

#include "imgui.h"

#include "ui/panels/panel.hpp"

namespace core
{
    class Engine;
}

namespace ui::panels
{
    using namespace core;

    class PerformancePanel final : public Panel
    {
    public:
        PerformancePanel() = default;
        ~PerformancePanel() override = default;

        void Render() override;

        void SetEngine(const Engine* engine) { m_Engine = engine; }

    private:
        const Engine* m_Engine = nullptr;
    };
}
