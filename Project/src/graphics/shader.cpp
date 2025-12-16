#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

#include <glm/gtc/type_ptr.hpp>

#include "graphics/shader.hpp"
#include "utils/file_utils.hpp"

namespace graphics
{
    using namespace std;

    Shader::Shader(const string& vertexPath, const string& fragmentPath)
        : m_RendererID(0)
    {
        // Read shader source files
        const string vertexSource = ReadFile(vertexPath);
        const string fragmentSource = ReadFile(fragmentPath);

        // Compile shaders
        const GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
        const GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

        // Link shaders into a program
        Link(vertexShader, fragmentShader);

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

    GLuint Shader::CompileShader(const GLenum type, const string& source)
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

            cerr
                << "[Shader Error] "
                << (type == GL_VERTEX_SHADER ? "Vertex" : "Fragment")
                << " shader compilation failed:\n"
                << infoLog << endl;

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

            cerr
                << "[Shader Error] Program linking failed:\n"
                << infoLog
                << endl;

            glDeleteProgram(m_RendererID);
            m_RendererID = 0;
        }
    }

    string Shader::ReadFile(const string& filepath)
    {
        // Use file utility to read a shader file
        string content = utils::file::ReadFile(filepath);

        if (content.empty())
        {
            cerr << "[Shader Error] Failed to read shader file: " << filepath << endl;
            cerr << "Current working directory: " << filesystem::current_path() << endl;
        }

        return content;
    }

    GLint Shader::GetUniformLocation(const string& name) const
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
            cerr << "[Shader Warning] Uniform '" << name << "' doesn't exist!" << endl;
        }

        m_UniformLocationCache[name] = location;

        return location;
    }

    // Uniform setters implementation
    void Shader::SetBool(const string& name, const bool value) const
    {
        glUniform1i(GetUniformLocation(name), static_cast<int>(value));
    }

    void Shader::SetInt(const string& name, const int value) const
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void Shader::SetFloat(const string& name, const float value) const
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void Shader::SetVec2(const string& name, const vec2& value) const
    {
        glUniform2fv(GetUniformLocation(name), 1, value_ptr(value));
    }

    void Shader::SetVec3(const string& name, const vec3& value) const
    {
        glUniform3fv(GetUniformLocation(name), 1, value_ptr(value));
    }

    void Shader::SetVec4(const string& name, const vec4& value) const
    {
        glUniform4fv(GetUniformLocation(name), 1, value_ptr(value));
    }

    void Shader::SetMat3(const string& name, const mat3& value) const
    {
        glUniformMatrix3fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr(value));
    }

    void Shader::SetMat4(const string& name, const mat4& value) const
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, value_ptr(value));
    }
}
