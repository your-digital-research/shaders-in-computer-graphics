#include <iostream>

#include "platform/window.hpp"
#include "graphics/renderer.hpp"

namespace platform
{
    Window::Window(const int width, const int height, const std::string& title)
        : m_Width(width),
          m_Height(height)
    {
        // Try to initialize GLFW
        if (!glfwInit())
        {
            std::cerr << "[GLFW Error] Failed to initialize GLFW!" << std::endl;

            std::exit(EXIT_FAILURE);
        }

        // Set GLFW window hints
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
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

            std::exit(EXIT_FAILURE);
        }

        // Make the window's context current
        glfwMakeContextCurrent(m_Window);

        // Set callbacks
        glfwSetWindowUserPointer(m_Window, this);
        glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);
        glfwSetWindowFocusCallback(m_Window, WindowFocusCallback);
        glfwSetWindowSizeCallback(m_Window, WindowSizeCallback);

        // Set size limits (minimum 640x360 - half of 1280x720)
        glfwSetWindowSizeLimits(m_Window, 640, 360, GLFW_DONT_CARE, GLFW_DONT_CARE);

        // Enable V-Sync
        glfwSwapInterval(1);

        // std::cout << "Window created successfully!" << std::endl;
    }

    Window::~Window()
    {
        glfwDestroyWindow(m_Window);

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

    void Window::SwapBuffers() const
    {
        glfwSwapBuffers(m_Window);
    }

    void Window::OnFramebufferResize()
    {
        int width, height;

        glfwGetFramebufferSize(m_Window, &width, &height);

        m_Width = width;
        m_Height = height;

        graphics::Renderer::SetViewport(0, 0, width, height);
    }

    void Window::OnWindowFocus()
    {
        OnFramebufferResize();
    }

    void Window::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        if (auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window)))
        {
            windowInstance->m_Width = width;
            windowInstance->m_Height = height;
            windowInstance->OnFramebufferResize();
        }
    }

    void Window::WindowFocusCallback(GLFWwindow* window, int focused)
    {
        if (!focused) return;

        if (auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window)))
        {
            windowInstance->OnWindowFocus();
        }
    }

    void Window::WindowSizeCallback(GLFWwindow* window, int width, int height)
    {
        if (auto* windowInstance = static_cast<Window*>(glfwGetWindowUserPointer(window)))
        {
            windowInstance->m_Width = width;
            windowInstance->m_Height = height;
        }
    }
}
