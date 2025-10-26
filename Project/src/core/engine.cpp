#include <iostream>

#include "core/engine.hpp"

namespace core
{
    Engine::Engine(platform::Window* window)
        : m_Window(window), m_Renderer(nullptr), m_Running(true)
    {
        Initialize();
    }

    void Engine::Initialize()
    {
        // Create a Renderer after OpenGL context is created
        m_Renderer = new graphics::Renderer();

        // Set the initial clear color
        m_Renderer->SetClearColor(0.2f, 0.3f, 0.3f, 1.0f);

        // Set the initial viewport
        graphics::Renderer::SetViewport(0, 0, 800, 600);
    }

    void Engine::Run() const
    {
        while (m_Running && !m_Window->ShouldClose())
        {
            // Poll for events
            m_Window->PollEvents();

            // Clear the screen
            m_Renderer->Clear();

            // TODO: Update and render active scene here

            // Swap buffers
            m_Window->SwapBuffers();
        }
    }
}
