#include "graphics/shader.hpp"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <glm/gtc/type_ptr.hpp>

#include "utils/file_utils.hpp"

namespace graphics
{
    Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
    {
        // Read shader source files
        const std::string vertexSource = ReadFile(vertexPath);
        const std::string fragmentSource = ReadFile(fragmentPath);

        if (vertexSource.empty())
        {
            throw std::runtime_error("Failed to read vertex shader: " + vertexPath);
        }

        if (fragmentSource.empty())
        {
            throw std::runtime_error("Failed to read fragment shader: " + fragmentPath);
        }

        // Compile shaders
        const GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
        const GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

        if (vertexShader == 0)
        {
            throw std::runtime_error("Failed to compile vertex shader: " + vertexPath);
        }

        if (fragmentShader == 0)
        {
            glDeleteShader(vertexShader);

            throw std::runtime_error("Failed to compile fragment shader: " + fragmentPath);
        }

        // Link shaders into a program
        Link(vertexShader, fragmentShader);

        if (m_RendererID == 0)
        {
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            throw std::runtime_error("Failed to link shader program");
        }

        // Delete individual shaders (they're now linked into the program)
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_RendererID);
    }

    void Shader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void Shader::Unbind()
    {
        glUseProgram(0);
    }

    GLuint Shader::CompileShader(const GLenum type, const std::string& source)
    {
        // Create shader
        const GLuint shader = glCreateShader(type);
        const char* src = source.c_str();

        // Set source and compile
        glShaderSource(shader, 1, &src, nullptr);
        glCompileShader(shader);

        // Check compilation status
        GLint success;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            GLchar infoLog[512];

            glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);

            std::cerr
                << "[Shader Error] "
                << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                << " shader compilation failed:\n"
                << infoLog
                << std::endl;

            glDeleteShader(shader);

            return 0;
        }

        return shader;
    }

    void Shader::Link(const GLuint vertexShader, const GLuint fragmentShader)
    {
        // Create a program and attach shaders
        m_RendererID = glCreateProgram();
        glAttachShader(m_RendererID, vertexShader);
        glAttachShader(m_RendererID, fragmentShader);

        // Link program
        glLinkProgram(m_RendererID);

        // Check linking status
        GLint success;
        glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);

        if (!success)
        {
            GLchar infoLog[512];

            glGetProgramInfoLog(m_RendererID, sizeof(infoLog), nullptr, infoLog);

            std::cerr
                << "[Shader Error] Program linking failed:\n"
                << infoLog
                << std::endl;

            glDeleteProgram(m_RendererID);
            m_RendererID = 0;
        }
    }

    std::string Shader::ReadFile(const std::string& filepath)
    {
        // Use file utility to read a shader file
        std::string content = utils::file::ReadFile(filepath);

        if (content.empty())
        {
            std::cerr << "[Shader Error] Failed to read shader file: " << filepath << std::endl;
            std::cerr << "Current working directory: " << std::filesystem::current_path() << std::endl;
        }

        return content;
    }

    GLint Shader::GetUniformLocation(const std::string& name) const
    {
        // Check if the uniform location is already in cache
        if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        {
            return m_UniformLocationCache[name];
        }

        // If not in cache, get it from OpenGL and cache it
        const GLint location = glGetUniformLocation(m_RendererID, name.c_str());

        if (location == -1)
        {
            std::cerr << "[Shader Warning] Uniform '" << name << "' doesn't exist!" << std::endl;
        }

        m_UniformLocationCache[name] = location;

        return location;
    }

    // Uniform setters implementation
    void Shader::SetBool(const std::string& name, const bool value) const
    {
        glUniform1i(GetUniformLocation(name), static_cast<int>(value));
    }

    void Shader::SetInt(const std::string& name, const int value) const
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetFloat(const std::string& name, const float value) const
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetVec2(const std::string& name, const glm::vec2& value) const
    {
        glUniform2fv(GetUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVec3(const std::string& name, const glm::vec3& value) const
    {
        glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::SetVec4(const std::string& name, const glm::vec4& value) const
    {
        glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
    }

    void Shader::SetMat3(const std::string& name, const glm::mat3& value) const
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetMat4(const std::string& name, const glm::mat4& value) const
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
    }
}
