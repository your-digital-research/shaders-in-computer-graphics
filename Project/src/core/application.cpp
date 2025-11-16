#include <iostream>

#include "core/application.hpp"
#include "platform/window.hpp"

namespace core
{
    using namespace std;
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
        m_Window = new Window(1280, 720, "Shaders In Computer Graphics");
        m_Engine = new Engine(m_Window);

        cout << "Application initialized successfully!" << endl;
    }

    void Application::Shutdown()
    {
        delete m_Window;
        delete m_Engine;

        m_Window = nullptr;
        m_Engine = nullptr;

        cout << "Application shutdown successfully!" << endl;
    }
}
