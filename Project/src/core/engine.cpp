#include "core/engine.hpp"

namespace core
{
    using namespace platform;
    using namespace graphics;

    Engine::Engine(Window* window)
        : m_Window(window),
          m_Renderer(nullptr),
          m_SceneManager(window),
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
        m_Renderer = new Renderer();

        // Set Renderer defaults
        Renderer::SetClearColor(0.15f, 0.18f, 0.22f, 1.0f);
        Renderer::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

        // Initialize scenes after a renderer is set up
        m_SceneManager.InitializeDefaultScenes();
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
            Window::PollEvents();

            // Calculate delta time
            const float deltaTime = CalculateDeltaTime();

            // Update scene (includes aspect ratio update)
            m_SceneManager.UpdateActiveScene(deltaTime);

            // Clear screen
            Renderer::Clear();

            // Render scene
            m_SceneManager.RenderActiveScene();

            // Swap buffers
            m_Window->SwapBuffers();
        }
    }
}
