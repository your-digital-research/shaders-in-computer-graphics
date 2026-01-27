#include "core/engine.hpp"

#include <stdexcept>

namespace core
{
    using namespace platform;
    using namespace graphics;

    Engine::Engine(Window* window)
        : m_Window(window),
          m_SceneManager(window),
          m_LastFrameTime(static_cast<float>(glfwGetTime()))
    {
        if (!m_Window)
        {
            throw std::invalid_argument("Window pointer cannot be null!");
        }

        Initialize();
    }

    Engine::~Engine()
    {
        Shutdown();
    }

    void Engine::Initialize()
    {
        try
        {
            m_Renderer = new Renderer();

            if (!m_Renderer)
            {
                throw std::runtime_error("Failed to create Renderer!");
            }

            m_UIManager = new UIManager(m_Window);

            if (!m_UIManager)
            {
                throw std::runtime_error("Failed to create UIManager!");
            }

            m_Window->InitializeRenderer();
            m_SceneManager.InitializeDefaultScenes();
            m_UIManager->InitializePanels(this);
        }
        catch (...)
        {
            Shutdown();

            throw;
        }
    }

    void Engine::Shutdown()
    {
        delete m_UIManager;
        delete m_Renderer;

        m_UIManager = nullptr;
        m_Renderer = nullptr;
    }

    float Engine::GetDeltaTime()
    {
        const auto currentTime = static_cast<float>(glfwGetTime());

        m_CurrentDeltaTime = currentTime - m_LastFrameTime;
        m_LastFrameTime = currentTime;

        return m_CurrentDeltaTime;
    }

    void Engine::Update()
    {
        m_SceneManager.UpdateActiveScene(GetDeltaTime());
    }

    void Engine::Render() const
    {
        Renderer::Clear();

        m_SceneManager.RenderActiveScene();
    }

    void Engine::DrawUI() const
    {
        m_UIManager->BeginFrame();
        m_UIManager->RenderUI();
        m_UIManager->EndFrame();
    }

    void Engine::Run()
    {
        if (!m_Window || !m_Renderer || !m_UIManager)
        {
            throw std::runtime_error("Engine components not properly initialized!");
        }

        while (m_Running && !m_Window->ShouldClose())
        {
            m_Window->PollEvents();

            Update();
            Render();
            DrawUI();

            m_Window->SwapBuffers();
        }
    }
}
