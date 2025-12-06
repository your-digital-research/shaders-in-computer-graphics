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
        m_Renderer = new Renderer();

        Renderer::SetClearColor(Color::RGB(0.15f, 0.18f, 0.22f));
        Renderer::SetViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());

        m_SceneManager.InitializeDefaultScenes();
    }

    void Engine::Shutdown()
    {
        delete m_Renderer;

        m_Renderer = nullptr;
    }

    float Engine::GetDeltaTime()
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
            Window::PollEvents();

            m_SceneManager.UpdateActiveScene(GetDeltaTime());

            Renderer::Clear();

            m_SceneManager.RenderActiveScene();
            m_Window->SwapBuffers();
        }
    }
}
