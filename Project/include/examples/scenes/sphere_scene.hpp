#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace scene;
    using namespace graphics;

    enum class SphereColorTheme
    {
        Unknown,
        CyberGlow,
        FireBall,
        IceSphere,
        NeonPink,
        EnergyShield,
        AuroraBorealis,
        SunsetGlow,
        ToxicWaste,
        DeepSpace,
        HologramBlue
    };

    class SphereScene final : public Scene
    {
    public:
        SphereScene();
        ~SphereScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        Mesh* m_SphereMesh;
        Shader* m_Shader;

        glm::mat4 m_ModelMatrix;

        float m_RotationAngle;
        float m_RotationSpeed;
        float m_PulseSpeed;
        float m_Time;

        float m_SphereRadius;
        int m_Segments;
        int m_Rings;

        float m_RimPower;
        float m_RimIntensity;

        Color m_RimColor = Color::White;
        Color m_CoreColor = Color::White;
        SphereColorTheme m_CurrentColorTheme = SphereColorTheme::Unknown;

        void CreateSphere(float radius, unsigned int segments, unsigned int rings);
        void SetColorTheme(SphereColorTheme theme);
    };
}
