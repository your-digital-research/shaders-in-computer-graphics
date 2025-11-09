#include <iostream>

#include "core/application.hpp"
#include "platform/window.hpp"

namespace core
{
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
        m_Window = new platform::Window(1280, 720, "Shaders In Computer Graphics");
        m_Engine = new Engine(m_Window);

        std::cout << "Application initialized successfully!" << std::endl;
    }

    void Application::Shutdown()
    {
        delete m_Window;
        delete m_Engine;

        m_Window = nullptr;
        m_Engine = nullptr;

        std::cout << "Application shutdown successfully!" << std::endl;
    }
}
