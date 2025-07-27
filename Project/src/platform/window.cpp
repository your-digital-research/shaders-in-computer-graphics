#include "platform/window.hpp"
#include <iostream>

Window::Window(const int width, const int height, const std::string &title)
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

    // Create the GLFW window
    m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    // Check if the window was created successfully
    if (!m_Window)
    {
        std::cerr << "[GLFW Error] Failed to create GLFW window!" << std::endl;

        glfwTerminate();

        std::exit(EXIT_FAILURE);
    }

    // Make the window's context current
    glfwMakeContextCurrent(m_Window);

    // Enable V-Sync
    glfwSwapInterval(1);
}

Window::~Window()
{
    glfwDestroyWindow(m_Window);

    glfwTerminate();
}

GLFWwindow *Window::GetNativeWindow() const
{
    return m_Window;
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(m_Window);
}

void Window::PollEvents() const
{
    glfwPollEvents();
}

void Window::SwapBuffers() const
{
    glfwSwapBuffers(m_Window);
}