#include "platform/window.hpp"

#include <iostream>
#include <stdexcept>

#include "constants/graphics_constants.hpp"
#include "graphics/renderer.hpp"

namespace platform
{
    using namespace graphics;

    Window::Window(const int width, const int height, const std::string& title)
        : m_Width(width),
          m_Height(height)
    {
        // Try to initialize GLFW
        if (!glfwInit())
        {
            std::cerr << "[GLFW Error] Failed to initialize GLFW!" << std::endl;

            throw std::runtime_error("Failed to initialize GLFW!");
        }

        // Set GLFW window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, constants::graphics::OPENGL_MAJOR_VERSION);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, constants::graphics::OPENGL_MINOR_VERSION);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
        // macOS specific hint for OpenGL compatibility
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

        // Disable window resizing
        // glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

        // Enable window resizing with size constraints
        glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
        glfwWindowHint(GLFW_DECORATED, GLFW_TRUE); // Enable window decorations for min/max buttons

        // Create the GLFW window
        m_Window = glfwCreateWindow(m_Width, m_Height, title.c_str(), nullptr, nullptr);

        // Check if the window was created successfully
        if (!m_Window)
        {
            std::cerr << "[GLFW Error] Failed to create GLFW window!" << std::endl;

            glfwTerminate();

            throw std::runtime_error("Failed to create GLFW window!");
        }

        // Make the window's context current
        glfwMakeContextCurrent(m_Window);

        // Set callbacks
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
        glfwSetWindowFocusCallback(m_Window, WindowFocusCallback);
        glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);

        // Set size limits (minimum half of default size)
        glfwSetWindowSizeLimits(m_Window,
                                constants::graphics::DEFAULT_WINDOW_WIDTH / 2,
                                constants::graphics::DEFAULT_WINDOW_HEIGHT / 2,
                                GLFW_DONT_CARE, GLFW_DONT_CARE);

        // Enable V-Sync
        glfwSwapInterval(1);
    }

    Window::~Window()
    {
        if (m_Window)
        {
            glfwDestroyWindow(m_Window);

            m_Window = nullptr;
        }

        glfwTerminate();
    }

    GLFWwindow* Window::GetNativeWindow() const
    {
        return m_Window;
    }

    bool Window::ShouldClose() const
    {
        return glfwWindowShouldClose(m_Window);
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers()
    {
        glfwSwapBuffers(m_Window);
    }

    void Window::OnFramebufferResize()
    {
        int width, height;

        glfwGetFramebufferSize(m_Window, &width, &height);

        m_Width = width;
        m_Height = height;

        Renderer::SetViewport(0, 0, m_Width, m_Height);
    }

    void Window::OnWindowFocus()
    {
        OnFramebufferResize();
    }

    void Window::InitializeRenderer() const
    {
        Renderer::SetBackgroundColor(constants::graphics::DEFAULT_BACKGROUND_COLOR);
        Renderer::SetViewport(0, 0, m_Width, m_Height);
    }

    void Window::FramebufferSizeCallback(GLFWwindow* window, const int width, const int height)
    {
        if (auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window)))
        {
            windowInstance->m_Width = width;
            windowInstance->m_Height = height;
            windowInstance->OnFramebufferResize();
        }
    }

    void Window::WindowFocusCallback(GLFWwindow* window, const int focused)
    {
        if (!focused) return;

        if (auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window)))
        {
            windowInstance->OnWindowFocus();
        }
    }

    void Window::WindowSizeCallback(GLFWwindow* window, const int width, const int height)
    {
        if (auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window)))
        {
            windowInstance->m_Width = width;
            windowInstance->m_Height = height;
        }
    }
}
