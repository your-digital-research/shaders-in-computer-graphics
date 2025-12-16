#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

#include "graphics/gl.hpp"

namespace graphics
{
    using namespace std;
    using namespace glm;

    class Shader
    {
    public:
        Shader(const string& vertexPath, const string& fragmentPath);
        ~Shader();

        void Bind() const;
        static void Unbind();

        void SetBool(const string& name, bool value) const;
        void SetInt(const string& name, int value) const;
        void SetFloat(const string& name, float value) const;

        void SetVec2(const string& name, const vec2& value) const;
        void SetVec3(const string& name, const vec3& value) const;
        void SetVec4(const string& name, const vec4& value) const;

        void SetMat3(const string& name, const mat3& value) const;
        void SetMat4(const string& name, const mat4& value) const;

    private:
        GLuint m_RendererID;
        mutable unordered_map<string, GLint> m_UniformLocationCache;

        static GLuint CompileShader(GLenum type, const string& source);
        void Link(GLuint vertexShader, GLuint fragmentShader);

        static string ReadFile(const string& filepath);
        GLint GetUniformLocation(const string& name) const;
    };
}
