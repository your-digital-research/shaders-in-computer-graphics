#pragma once

#include <string>
#include <unordered_map>

#include "graphics/gl.hpp"
#include <glm/glm.hpp>

namespace graphics
{
    using namespace std;
    using namespace glm;

    class Shader
    {
    public:
        // Constructor and Destructor
        Shader(const string& vertexPath, const string& fragmentPath);
        ~Shader();

        // Shader operations
        void Bind() const;
        static void Unbind();

        // Uniform setters
        void SetBool(const string& name, bool value) const;
        void SetInt(const string& name, int value) const;
        void SetFloat(const string& name, float value) const;
        void SetVec2(const string& name, const vec2& value) const;
        void SetVec3(const string& name, const vec3& value) const;
        void SetVec4(const string& name, const vec4& value) const;
        void SetMat3(const string& name, const mat3& value) const;
        void SetMat4(const string& name, const mat4& value) const;

    private:
        // Shader program ID
        GLuint m_RendererID;

        // Cache for uniform locations
        mutable unordered_map<string, GLint> m_UniformLocationCache;

        // Shader compilation and linking
        static GLuint CompileShader(GLenum type, const string& source);
        void Link(GLuint vertexShader, GLuint fragmentShader);

        // Utility functions
        static string ReadFile(const string& filepath);
        GLint GetUniformLocation(const string& name) const;
    };
}
