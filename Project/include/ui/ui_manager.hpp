#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "platform/window.hpp"

namespace core
{
    class Engine;
}

namespace ui
{
    using namespace core;
    using namespace platform;

    class UIManager
    {
    public:
        // Constructor and Destructor
        explicit UIManager(const Window* window);
        ~UIManager();

        // Frame management
        void BeginFrame() const;
        void EndFrame() const;

        // UI rendering
        void RenderUI() const;

        // Enable / Disable UI
        void SetEnabled(const bool enabled) { m_Enabled = enabled; }
        [[nodiscard]] bool IsEnabled() const { return m_Enabled; }

    private:
        // Member variables
        bool m_Enabled;
    };
}
