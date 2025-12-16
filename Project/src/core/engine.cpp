#include "core/engine.hpp"

namespace core
{
    using namespace platform;
    using namespace graphics;

    Engine::Engine(Window* window)
        : m_Window(window),
          m_Renderer(nullptr),
          m_UIManager(nullptr),
          m_SceneManager(window),
          m_LastFrameTime(static_cast<float>(glfwGetTime())),
          m_CurrentDeltaTime(0.0f),
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
        m_UIManager = new UIManager(m_Window);

        m_Window->InitializeRenderer();
        m_SceneManager.InitializeDefaultScenes();
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
