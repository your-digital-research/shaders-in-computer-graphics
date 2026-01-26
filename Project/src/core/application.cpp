#include "core/application.hpp"

#include "constants/graphics_constants.hpp"

namespace core
{
    using namespace platform;

    Application::Application()
    {
        Initialize();
    }

    Application::~Application()
    {
        Shutdown();
    }

    void Application::Run() const
    {
        m_Engine->Run();
    }

    void Application::Initialize()
    {
        m_Window = new Window(constants::graphics::DEFAULT_WINDOW_WIDTH,
                              constants::graphics::DEFAULT_WINDOW_HEIGHT,
                              constants::graphics::DEFAULT_WINDOW_TITLE);
        m_Engine = new Engine(m_Window);
    }

    void Application::Shutdown()
    {
        delete m_Window;
        delete m_Engine;

        m_Window = nullptr;
        m_Engine = nullptr;
    }
}
