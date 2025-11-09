#pragma once

#include "platform/window.hpp"
#include "graphics/renderer.hpp"
#include "scene/scene_manager.hpp"

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

        // Scene management
        scene::SceneManager& GetSceneManager() { return m_SceneManager; }

    private:
        // Member variables
        platform::Window* m_Window;
        graphics::Renderer* m_Renderer;
        scene::SceneManager m_SceneManager;

        // Timing
        float m_LastFrameTime;

        // Engine state
        bool m_Running;

        // Initialization and cleanup
        void Initialize();
        void Shutdown();
    };
}
