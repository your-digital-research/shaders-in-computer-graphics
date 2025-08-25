#include <iostream>

#include "core/engine.hpp"

Engine::Engine(Window* window)
    : m_Window(window), m_Running(true)
{
    std::cout << "Engine created successfully!" << std::endl;
}

void Engine::Run() const
{
    while (m_Running && !m_Window->ShouldClose())
    {
        m_Window->PollEvents();

        // Coloring the window with a gray color
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Window->SwapBuffers();
    }
}
