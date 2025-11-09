#pragma once

#include "platform/window.hpp"
#include "graphics/renderer.hpp"
#include "scene/cube_scene.hpp"

namespace core
{
    class Engine
    {
    public:
        // Constructor and Destructor
        explicit Engine(platform::Window* window);
        ~Engine();

        // Engine management
        void Run();

    private:
        // Member variables
        platform::Window* m_Window;
        graphics::Renderer* m_Renderer;
        scene::Scene* m_ActiveScene;

        // Timing
        float m_LastFrameTime;

        // Engine state
        bool m_Running;

        // Initialization and cleanup
        void Initialize();
        void Shutdown();
    };
}
