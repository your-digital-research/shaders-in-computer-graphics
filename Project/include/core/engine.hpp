#pragma once

#include "platform/window.hpp"
#include "graphics/renderer.hpp"

namespace core
{
    class Engine
    {
    public:
        // Constructor and Destructor
        explicit Engine(platform::Window* window);
        ~Engine() = default;

        // Engine management
        void Run() const;

    private:
        // Member variables
        platform::Window* m_Window;
        graphics::Renderer* m_Renderer;

        // Engine state
        bool m_Running;

        // Initialization
        void Initialize();
    };
}
