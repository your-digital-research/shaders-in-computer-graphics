#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
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

        [[nodiscard]] glm::vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] glm::vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

        [[nodiscard]] const Color& GetTopColor() const { return m_TopColor; }
        [[nodiscard]] const Color& GetBottomLeftColor() const { return m_BottomLeftColor; }
        [[nodiscard]] const Color& GetBottomRightColor() const { return m_BottomRightColor; }
        [[nodiscard]] float GetTriangleSize() const { return m_TriangleSize; }

        void SetTopColor(const Color& color);
        void SetBottomLeftColor(const Color& color);
        void SetBottomRightColor(const Color& color);
        void SetTriangleSize(float size);

        void SetTopPosition(const glm::vec3& position);
        void SetBottomLeftPosition(const glm::vec3& position);
        void SetBottomRightPosition(const glm::vec3& position);

    private:
        Mesh* m_TriangleMesh;
        Shader* m_Shader;

        glm::mat4 m_ModelMatrix;

        float m_TriangleSize;
        float m_DefaultTriangleSize;

        Color m_TopColor;
        Color m_BottomLeftColor;
        Color m_BottomRightColor;

        Color m_DefaultTopColor;
        Color m_DefaultBottomLeftColor;
        Color m_DefaultBottomRightColor;

        glm::vec3 m_TopPosition;
        glm::vec3 m_BottomLeftPosition;
        glm::vec3 m_BottomRightPosition;

        glm::vec3 m_DefaultTopPosition;
        glm::vec3 m_DefaultBottomLeftPosition;
        glm::vec3 m_DefaultBottomRightPosition;

        glm::vec3 m_BaseTopPosition;
        glm::vec3 m_BaseBottomLeftPosition;
        glm::vec3 m_BaseBottomRightPosition;

        glm::vec3 m_DefaultCameraPosition;
        glm::vec3 m_DefaultCameraRotation;

        void CreateTriangle();
    };
}
