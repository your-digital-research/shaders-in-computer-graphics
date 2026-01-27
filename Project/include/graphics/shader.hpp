#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "graphics/gl.hpp"

namespace graphics
{
    class Shader
    {
    public:
        Shader(const std::string& vertexPath, const std::string& fragmentPath);
        ~Shader();

        void Bind() const;
        static void Unbind();

        void SetBool(const std::string& name, bool value) const;
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;

        void SetVec2(const std::string& name, const glm::vec2& value) const;
        void SetVec3(const std::string& name, const glm::vec3& value) const;
        void SetVec4(const std::string& name, const glm::vec4& value) const;

        void SetMat3(const std::string& name, const glm::mat3& value) const;
        void SetMat4(const std::string& name, const glm::mat4& value) const;

    private:
        GLuint m_RendererID = 0;
        mutable std::unordered_map<std::string, GLint> m_UniformLocationCache;

        static GLuint CompileShader(GLenum type, const std::string& source);
        void Link(GLuint vertexShader, GLuint fragmentShader);

        static std::string ReadFile(const std::string& filepath);
        GLint GetUniformLocation(const std::string& name) const;
    };
}
