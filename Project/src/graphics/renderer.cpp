#include "graphics/renderer.hpp"

#include <iostream>
#include <stdexcept>

#include "constants/graphics_constants.hpp"
#include "graphics/gl.hpp"

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

            throw std::runtime_error("Failed to initialize GLAD!");
        }

        // Print OpenGL version
        // std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
        // std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
        // std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
        // std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

        // Set default OpenGL state
        if (constants::graphics::DEFAULT_DEPTH_TEST) EnableDepthTest();
        if (constants::graphics::DEFAULT_BLENDING) EnableBlending();

        // Set default depth function
        glDepthFunc(GL_LESS);

        // Set default blend function
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Reset depth buffer
        glClearDepth(1.0f);
    }

    void Renderer::SetBackgroundColor(const Color& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
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

    void Renderer::SetBlendModeAlpha()
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void Renderer::SetBlendModeAdditive()
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    }

    void Renderer::SetBlendModeMultiply()
    {
        glBlendFunc(GL_DST_COLOR, GL_ZERO);
    }

    void Renderer::SetPolygonModeFill()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    void Renderer::SetPolygonModeWireframe()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    void Renderer::SetPolygonModePoint()
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }

    void Renderer::SetViewport(const int x, const int y, const int width, const int height)
    {
        glViewport(x, y, width, height);
    }
}
