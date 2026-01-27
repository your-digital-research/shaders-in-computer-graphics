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

        void RenderSettings() override;
        void ResetToDefault() override;

        [[nodiscard]] glm::vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] glm::vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

        [[nodiscard]] float GetSphereRadius() const { return m_SphereRadius; }
        [[nodiscard]] int GetSegments() const { return m_Segments; }
        [[nodiscard]] int GetRings() const { return m_Rings; }
        [[nodiscard]] float GetRotationSpeed() const { return m_RotationSpeed; }
        [[nodiscard]] float GetPulseSpeed() const { return m_PulseSpeed; }
        [[nodiscard]] float GetRimPower() const { return m_RimPower; }
        [[nodiscard]] float GetRimIntensity() const { return m_RimIntensity; }

        void SetSphereRadius(float radius);
        void SetSegments(int segments);
        void SetRings(int rings);

        void SetRotationSpeed(float speed);
        void SetPulseSpeed(float speed);

        void SetRimIntensity(float intensity);
        void SetRimPower(float power);

        void SetCoreColor(const Color& color);
        void SetRimColor(const Color& color);

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

        Color m_RimColor;
        Color m_CoreColor;
        SphereColorTheme m_CurrentColorTheme;

        float m_DefaultSphereRadius;

        int m_DefaultSegments;
        int m_DefaultRings;

        float m_DefaultRotationSpeed;
        float m_DefaultPulseSpeed;
        float m_DefaultRimPower;
        float m_DefaultRimIntensity;

        SphereColorTheme m_DefaultColorTheme;

        glm::vec3 m_DefaultCameraPosition;
        glm::vec3 m_DefaultCameraRotation;

        void CreateSphere(float radius, unsigned int segments, unsigned int rings);
        void SetColorTheme(SphereColorTheme theme);
    };
}
