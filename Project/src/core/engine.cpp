#include <iostream>
#include <memory>

#include "core/engine.hpp"
#include "examples/scenes/cube_scene.hpp"

namespace core
{
    Engine::Engine(platform::Window* window)
        : m_Window(window),
          m_Renderer(nullptr),
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
        graphics::Renderer::SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        graphics::Renderer::SetViewport(0, 0, 800, 600);

        // Create and add the cube scene
        auto cubeScene = std::make_unique<examples::CubeScene>();
        m_SceneManager.AddScene("cube", std::move(cubeScene));
        m_SceneManager.SetActiveScene("cube");
    }

    void Engine::Shutdown()
    {
        delete m_Renderer;

        m_Renderer = nullptr;
    }

    float Engine::CalculateDeltaTime()
    {
        const auto currentTime = static_cast<float>(glfwGetTime());
        const float deltaTime = currentTime - m_LastFrameTime;

        m_LastFrameTime = currentTime;

        return deltaTime;
    }

    void Engine::Run()
    {
        while (m_Running && !m_Window->ShouldClose())
        {
            // Poll for events
            m_Window->PollEvents();

            // Calculate delta time
            const float deltaTime = CalculateDeltaTime();

            // Update scene
            m_SceneManager.UpdateActiveScene(deltaTime);

            // Clear screen
            graphics::Renderer::Clear();

            // Render scene
            m_SceneManager.RenderActiveScene();

            // Swap buffers
            m_Window->SwapBuffers();
        }
    }
}
