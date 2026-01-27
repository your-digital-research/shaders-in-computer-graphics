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
        QuadScene();
        ~QuadScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

        void RenderSettings() override;
        void ResetToDefault() override;

        [[nodiscard]] glm::vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] glm::vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

        [[nodiscard]] float GetQuadWidth() const { return m_QuadWidth; }
        [[nodiscard]] float GetQuadHeight() const { return m_QuadHeight; }

        void SetQuadWidth(float width);
        void SetQuadHeight(float height);

    private:
        Mesh* m_QuadMesh;
        Shader* m_Shader;

        glm::mat4 m_ModelMatrix;

        float m_QuadWidth;
        float m_QuadHeight;
        Color m_QuadColor;

        float m_DefaultQuadWidth;
        float m_DefaultQuadHeight;

        glm::vec3 m_DefaultCameraPosition;
        glm::vec3 m_DefaultCameraRotation;

        void CreateQuad();
    };
}
