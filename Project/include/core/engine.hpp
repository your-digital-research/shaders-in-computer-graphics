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
        Window* m_Window = nullptr;
        Renderer* m_Renderer = nullptr;
        UIManager* m_UIManager = nullptr;

        SceneManager m_SceneManager;

        float m_LastFrameTime = 0.0f;
        float m_CurrentDeltaTime = 0.0f;

        bool m_Running = true;

        void Initialize();
        void Shutdown();
        void Update();
        void Render() const;
        void DrawUI() const;
    };
}
