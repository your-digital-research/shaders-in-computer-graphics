#define GL_SILENCE_DEPRECATION

#include "core/application.hpp"
#include "platform/window.hpp"
#include <iostream>

Application::Application() : m_Window(nullptr)
{
    Initialize();
}

Application::~Application()
{
    Shutdown();
}

void Application::Run()
{
    StartLoop();
}

void Application::Initialize()
{
    m_Window = new Window(800, 600, "Shaders In Computer Graphics");

    std::cout << "Window initialized successfully!" << std::endl;
}

void Application::StartLoop()
{
    while (!m_Window->ShouldClose())
    {
        m_Window->PollEvents();

        // Coloring the window with a grey color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window->SwapBuffers();
    }
}

void Application::Shutdown()
{
    delete m_Window;

    m_Window = nullptr;

    std::cout << "Application shutdown successfully!" << std::endl;
}