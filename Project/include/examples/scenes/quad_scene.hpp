#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace scene;
    using namespace graphics;

    class QuadScene final : public Scene
    {
    public:
        explicit QuadScene(Camera* camera);
        ~QuadScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

        void ResetToDefault() override;
        void RenderSettings() override;

        [[nodiscard]] glm::vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] glm::vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

        [[nodiscard]] float GetQuadWidth() const { return m_QuadWidth; }
        [[nodiscard]] float GetQuadHeight() const { return m_QuadHeight; }

        void SetQuadWidth(float width);
        void SetQuadHeight(float height);

    private:
        Mesh* m_Mesh = nullptr;
        Shader* m_Shader = nullptr;

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

        float m_QuadWidth = 1.0f;
        float m_QuadHeight = 1.0f;

        Color m_QuadColor = Color::White;

        float m_DefaultQuadWidth = 1.0f;
        float m_DefaultQuadHeight = 1.0f;

        glm::vec3 m_DefaultCameraPosition = glm::vec3(0.0f, 0.0f, 2.5f);
        glm::vec3 m_DefaultCameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);

        void CreateQuad();
    };
}
