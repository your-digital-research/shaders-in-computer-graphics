#include <iostream>

#include "core/application.hpp"
#include "platform/window.hpp"

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
    m_Window = new Window(800, 600, "Shaders In Computer Graphics");
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
