#pragma once

#include "platform/window.hpp"
#include "graphics/renderer.hpp"
#include "ui/ui_manager.hpp"
#include "scene/scene_manager.hpp"

namespace core
{
    using namespace platform;
    using namespace graphics;
    using namespace scene;
    using namespace ui;

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
        [[nodiscard]] float GetCurrentDeltaTime() const { return m_CurrentDeltaTime; }

        // Scene management
        SceneManager& GetSceneManager() { return m_SceneManager; }

    private:
        // Member variables
        Window* m_Window;
        Renderer* m_Renderer;
        UIManager* m_UIManager;
        SceneManager m_SceneManager;

        // Timing
        float m_LastFrameTime;
        float m_CurrentDeltaTime;

        // Engine state
        bool m_Running;

        // Initialization and cleanup
        void Initialize();
        void Shutdown();

        // Main loop methods
        void Update();
        void Render() const;
        void DrawUI() const;
    };
}
