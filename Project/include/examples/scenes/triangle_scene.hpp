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
        explicit TriangleScene(Camera* camera);
        ~TriangleScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

        void ResetToDefault() override;
        void RenderSettings() override;

        [[nodiscard]] glm::vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] glm::vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

        [[nodiscard]] const Color& GetTopColor() const { return m_TopColor; }
        [[nodiscard]] const Color& GetBottomLeftColor() const { return m_BottomLeftColor; }
        [[nodiscard]] const Color& GetBottomRightColor() const { return m_BottomRightColor; }

        [[nodiscard]] float GetTriangleSize() const { return m_TriangleSize; }

        void SetTriangleSize(float size);

        void SetTopColor(const Color& color);
        void SetBottomLeftColor(const Color& color);
        void SetBottomRightColor(const Color& color);

        void SetTopPosition(const glm::vec3& position);
        void SetBottomLeftPosition(const glm::vec3& position);
        void SetBottomRightPosition(const glm::vec3& position);

    private:
        Mesh* m_Mesh = nullptr;
        Shader* m_Shader = nullptr;

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

        float m_TriangleSize = 1.0f;
        float m_DefaultTriangleSize = 1.0f;

        Color m_TopColor = Color::Red;
        Color m_BottomLeftColor = Color::Green;
        Color m_BottomRightColor = Color::Blue;

        Color m_DefaultTopColor = Color::Red;
        Color m_DefaultBottomLeftColor = Color::Green;
        Color m_DefaultBottomRightColor = Color::Blue;

        glm::vec3 m_TopPosition = glm::vec3(0.0f, 0.5f, 0.0f);
        glm::vec3 m_BottomLeftPosition = glm::vec3(-0.5f, -0.5f, 0.0f);
        glm::vec3 m_BottomRightPosition = glm::vec3(0.5f, -0.5f, 0.0f);

        glm::vec3 m_DefaultTopPosition = glm::vec3(0.0f, 0.5f, 0.0f);
        glm::vec3 m_DefaultBottomLeftPosition = glm::vec3(-0.5f, -0.5f, 0.0f);
        glm::vec3 m_DefaultBottomRightPosition = glm::vec3(0.5f, -0.5f, 0.0f);

        glm::vec3 m_BaseTopPosition = glm::vec3(0.0f, 0.5f, 0.0f);
        glm::vec3 m_BaseBottomLeftPosition = glm::vec3(-0.5f, -0.5f, 0.0f);
        glm::vec3 m_BaseBottomRightPosition = glm::vec3(0.5f, -0.5f, 0.0f);

        glm::vec3 m_DefaultCameraPosition = glm::vec3(0.0f, 0.0f, 2.5f);
        glm::vec3 m_DefaultCameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);

        void CreateTriangle();
    };
}
