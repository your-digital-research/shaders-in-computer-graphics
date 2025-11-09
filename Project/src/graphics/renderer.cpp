#include <iostream>

#include "graphics/renderer.hpp"

namespace graphics
{
    Renderer::Renderer()
    {
        Initialize();
    }

    void Renderer::Initialize()
    {
        // Initialize GLAD
        if (!gladLoadGL())
        {
            std::cerr << "[OpenGL Error] Failed to initialize GLAD!" << std::endl;

            return;
        }

        // Print OpenGL version
        // std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        // std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
        // std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
        // std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        // Set default OpenGL state
        EnableDepthTest();
        EnableBlending();

        // Set default depth function
        glDepthFunc(GL_LESS);

        // Set default blend function
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::Clear() const
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset depth buffer
        glClearDepth(1.0f);
    }

    void Renderer::SetClearColor(const float r, const float g, const float b, const float a) const
    {
        glClearColor(r, g, b, a);
    }

    void Renderer::EnableDepthTest()
    {
        glEnable(GL_DEPTH_TEST);
    }

    void Renderer::DisableDepthTest()
    {
        glDisable(GL_DEPTH_TEST);
    }

    void Renderer::EnableBlending()
    {
        glEnable(GL_BLEND);
    }

    void Renderer::DisableBlending()
    {
        glDisable(GL_BLEND);
    }

    void Renderer::SetViewport(const int x, const int y, const int width, const int height)
    {
        glViewport(x, y, width, height);
    }
}
