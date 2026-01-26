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
        CubeScene();
        ~CubeScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

        void RenderSettings() override;
        void ResetToDefault() override;

        [[nodiscard]] glm::vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] glm::vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

    private:
        Mesh* m_CubeMesh;
        Shader* m_Shader;

        glm::mat4 m_ModelMatrix;

        float m_RotationAngle;
        float m_RotationSpeed;
        glm::vec3 m_RotationAxis;

        float m_DefaultRotationSpeed;
        glm::vec3 m_DefaultRotationAxis;

        float m_CubeSize;
        float m_DefaultCubeSize;

        Color m_FrontColor = Color::White;
        Color m_BackColor = Color::White;
        Color m_RightColor = Color::White;
        Color m_LeftColor = Color::White;
        Color m_TopColor = Color::White;
        Color m_BottomColor = Color::White;
        CubeColorTheme m_CurrentColorTheme = CubeColorTheme::Unknown;
        CubeColorTheme m_DefaultColorTheme = CubeColorTheme::Unknown;

        glm::vec3 m_DefaultCameraPosition;
        glm::vec3 m_DefaultCameraRotation;

        void CreateCube();
        void SetColorTheme(CubeColorTheme theme);
    };
}
