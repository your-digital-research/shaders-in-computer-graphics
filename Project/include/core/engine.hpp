#pragma once

#include "graphics/renderer.hpp"
#include "platform/window.hpp"
#include "scene/scene_manager.hpp"
#include "ui/ui_manager.hpp"

namespace core
{
    using namespace platform;
    using namespace graphics;
    using namespace scene;
    using namespace ui;

    class Engine
    {
    public:
        explicit Engine(Window* window);
        ~Engine();

        void Run();

        [[nodiscard]] float GetDeltaTime();
        [[nodiscard]] float GetCurrentDeltaTime() const { return m_CurrentDeltaTime; }

        SceneManager& GetSceneManager() { return m_SceneManager; }

    private:
        Window* m_Window;
        Renderer* m_Renderer;
        UIManager* m_UIManager;
        SceneManager m_SceneManager;

        float m_LastFrameTime;
        float m_CurrentDeltaTime;
        bool m_Running;

        void Initialize();
        void Shutdown();
        void Update();
        void Render() const;
        void DrawUI() const;
    };
}
