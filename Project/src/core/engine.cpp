#include <iostream>

#include "core/engine.hpp"

namespace core
{
    Engine::Engine(platform::Window* window)
        : m_Window(window),
          m_Renderer(nullptr),
          m_ActiveScene(nullptr),
          m_LastFrameTime(static_cast<float>(glfwGetTime())),
          m_Running(true)
    {
        Initialize();
    }

    Engine::~Engine()
    {
        Shutdown();
    }

    void Engine::Initialize()
    {
        // Create renderer
        m_Renderer = new graphics::Renderer();
        m_Renderer->SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        graphics::Renderer::SetViewport(0, 0, 800, 600);

        // Create a test scene
        m_ActiveScene = new scene::CubeScene();
    }

    void Engine::Shutdown()
    {
        delete m_ActiveScene;
        delete m_Renderer;

        m_ActiveScene = nullptr;
        m_Renderer = nullptr;
    }

    void Engine::Run()
    {
        while (m_Running && !m_Window->ShouldClose())
        {
            // Poll for events
            m_Window->PollEvents();

            // Calculate delta time
            const auto currentTime = static_cast<float>(glfwGetTime());
            const float deltaTime = currentTime - m_LastFrameTime;

            m_LastFrameTime = currentTime;

            // Update scene
            if (m_ActiveScene) m_ActiveScene->OnUpdate(deltaTime);

            // Clear screen
            m_Renderer->Clear();

            // Render scene
            if (m_ActiveScene) m_ActiveScene->OnRender();

            // Swap buffers
            m_Window->SwapBuffers();
        }
    }
}
