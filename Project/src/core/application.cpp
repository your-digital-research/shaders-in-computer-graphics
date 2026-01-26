#include "core/application.hpp"

#include <stdexcept>

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
        if (!m_Engine)
        {
            throw std::runtime_error("Engine is not initialized!");
        }

        m_Engine->Run();
    }

    void Application::Initialize()
    {
        try
        {
            m_Window = new Window(constants::graphics::DEFAULT_WINDOW_WIDTH,
                                  constants::graphics::DEFAULT_WINDOW_HEIGHT,
                                  constants::graphics::DEFAULT_WINDOW_TITLE);

            if (!m_Window)
            {
                throw std::runtime_error("Failed to create Window!");
            }

            m_Engine = new Engine(m_Window);

            if (!m_Engine)
            {
                throw std::runtime_error("Failed to create Engine!");
            }
        }
        catch (...)
        {
            Shutdown();

            throw;
        }
    }

    void Application::Shutdown()
    {
        delete m_Engine;
        delete m_Window;

        m_Engine = nullptr;
        m_Window = nullptr;
    }
}
