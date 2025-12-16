#pragma once

#include "imgui.h"

namespace ui::panels
{
    class Panel
    {
    public:
        // Constructor and Destructor
        Panel() = default;
        virtual ~Panel() = default;

        // Disable copy and move semantics
        Panel(const Panel&) = delete;
        Panel& operator=(const Panel&) = delete;
        Panel(Panel&&) = delete;
        Panel& operator=(Panel&&) = delete;

        // Virtual function to render panel
        virtual void Render() = 0;

        // Panel state
        void SetEnabled(const bool enabled) { m_Enabled = enabled; }
        [[nodiscard]] bool IsEnabled() const { return m_Enabled; }

    protected:
        bool m_Enabled = true;
    };
}
