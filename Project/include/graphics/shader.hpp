#pragma once

#include <string>
#include <unordered_map>

#include "graphics/gl.hpp"
#include <glm/glm.hpp>

namespace graphics
{
    class Shader
    {
    public:
        // Constructor and Destructor
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        // Shader operations
        void Bind() const;
        static void Unbind();

        // Uniform setters
        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;
        void SetMat3(const std::string& name, const glm::mat3& value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;

    private:
        // Shader program ID
        GLuint m_RendererID;

        // Cache for uniform locations
        mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

        // Shader compilation and linking
        static GLuint CompileShader(GLenum type, const std::string& source);
        void Link(GLuint vertexShader, GLuint fragmentShader);

        // Utility functions
        static std::string ReadFile(const std::string& filepath);
        GLint GetUniformLocation(const std::string& name) const;
    };
}
