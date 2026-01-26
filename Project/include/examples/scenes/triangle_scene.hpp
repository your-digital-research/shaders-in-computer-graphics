#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace glm;
    using namespace scene;
    using namespace graphics;

    class TriangleScene final : public Scene
    {
    public:
        TriangleScene();
        ~TriangleScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

        void RenderSettings() override;
        void ResetToDefault() override;

        [[nodiscard]] vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

        [[nodiscard]] const Color& GetTopColor() const { return m_TopColor; }
        [[nodiscard]] const Color& GetBottomLeftColor() const { return m_BottomLeftColor; }
        [[nodiscard]] const Color& GetBottomRightColor() const { return m_BottomRightColor; }
        [[nodiscard]] float GetTriangleSize() const { return m_TriangleSize; }

        void SetTopColor(const Color& color);
        void SetBottomLeftColor(const Color& color);
        void SetBottomRightColor(const Color& color);
        void SetTriangleSize(float size);

        void SetTopPosition(const vec3& position);
        void SetBottomLeftPosition(const vec3& position);
        void SetBottomRightPosition(const vec3& position);

    private:
        Mesh* m_TriangleMesh;
        Shader* m_Shader;

        mat4 m_ModelMatrix;

        float m_TriangleSize;
        float m_DefaultTriangleSize;

        Color m_TopColor;
        Color m_BottomLeftColor;
        Color m_BottomRightColor;

        Color m_DefaultTopColor;
        Color m_DefaultBottomLeftColor;
        Color m_DefaultBottomRightColor;

        vec3 m_TopPosition;
        vec3 m_BottomLeftPosition;
        vec3 m_BottomRightPosition;

        vec3 m_DefaultTopPosition;
        vec3 m_DefaultBottomLeftPosition;
        vec3 m_DefaultBottomRightPosition;

        vec3 m_BaseTopPosition;
        vec3 m_BaseBottomLeftPosition;
        vec3 m_BaseBottomRightPosition;

        vec3 m_DefaultCameraPosition;
        vec3 m_DefaultCameraRotation;

        void CreateTriangle();
    };
}
