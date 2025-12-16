#pragma once

#include "imgui.h"

namespace ui::panels
{
    class Panel
    {
    public:
        Panel() = default;
        virtual ~Panel() = default;

        Panel(const Panel&) = delete;
        Panel& operator=(const Panel&) = delete;
        Panel(Panel&&) = delete;
        Panel& operator=(Panel&&) = delete;

        virtual void Render() = 0;

        void SetEnabled(const bool enabled) { m_Enabled = enabled; }
        [[nodiscard]] bool IsEnabled() const { return m_Enabled; }

    protected:
        bool m_Enabled = true;
    };
}
