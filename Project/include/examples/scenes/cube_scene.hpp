#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace scene;
    using namespace graphics;

    enum class CubeColorTheme
    {
        Unknown,
        PastelDream,
        NeonCyberpunk,
        OceanDepth,
        SunsetVibes,
        ForestNature,
        RoyalLuxury,
        FireAndIce,
        CandyPop,
        MonochromeGray,
        RainbowSpectrum
    };

    class CubeScene final : public Scene
    {
    public:
        explicit CubeScene(Camera* camera);
        ~CubeScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

        void ResetToDefault() override;
        void RenderSettings() override;

        [[nodiscard]] glm::vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] glm::vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

    private:
        Mesh* m_Mesh = nullptr;
        Shader* m_Shader = nullptr;

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

        glm::vec3 m_RotationAxis = glm::vec3(0.5f, 1.0f, 0.25f);
        float m_RotationAngle = 0.0f;
        float m_RotationSpeed = 30.0f;

        float m_CubeSize = 1.0f;

        Color m_FrontColor = Color::White;
        Color m_BackColor = Color::White;
        Color m_RightColor = Color::White;
        Color m_LeftColor = Color::White;
        Color m_TopColor = Color::White;
        Color m_BottomColor = Color::White;
        CubeColorTheme m_CurrentColorTheme = CubeColorTheme::MonochromeGray;

        glm::vec3 m_DefaultRotationAxis = glm::vec3(0.5f, 1.0f, 0.25f);

        float m_DefaultRotationSpeed = 30.0f;
        float m_DefaultCubeSize = 1.0f;

        CubeColorTheme m_DefaultColorTheme = CubeColorTheme::MonochromeGray;

        glm::vec3 m_DefaultCameraPosition = glm::vec3(0.0f, 0.0f, 4.0f);
        glm::vec3 m_DefaultCameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);

        void CreateCube();
        void SetColorTheme(CubeColorTheme theme);
    };
}
