#pragma once

#include "platform/window.hpp"
#include "graphics/renderer.hpp"
#include "scene/scene_manager.hpp"

namespace core
{
    using namespace platform;
    using namespace graphics;
    using namespace scene;

    class Engine
    {
    public:
        // Constructor and Destructor
        explicit Engine(Window* window);
        ~Engine();

        // Engine management
        void Run();

        // Timing
        [[nodiscard]] float GetDeltaTime();

        // Scene management
        SceneManager& GetSceneManager() { return m_SceneManager; }

    private:
        // Member variables
        Window* m_Window;
        Renderer* m_Renderer;
        SceneManager m_SceneManager;

        // Timing
        float m_LastFrameTime;

        // Engine state
        bool m_Running;

        // Initialization and cleanup
        void Initialize();
        void Shutdown();
    };
}
