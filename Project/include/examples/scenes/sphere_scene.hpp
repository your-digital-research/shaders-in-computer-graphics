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
        explicit SphereScene(Camera* camera);
        ~SphereScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

        void ResetToDefault() override;
        void RenderSettings() override;

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
        Mesh* m_Mesh = nullptr;
        Shader* m_Shader = nullptr;

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

        float m_RotationAngle = 0.0f;
        float m_RotationSpeed = 16.0f;
        float m_PulseSpeed = 2.0f;
        float m_Time = 0.0f;

        float m_SphereRadius = 1.0f;
        int m_Segments = 64;
        int m_Rings = 32;

        float m_RimPower = 2.0f;
        float m_RimIntensity = 4.0f;

        Color m_RimColor = Color::White;
        Color m_CoreColor = Color::White;
        SphereColorTheme m_CurrentColorTheme = SphereColorTheme::DeepSpace;

        float m_DefaultSphereRadius = 1.0f;

        int m_DefaultSegments = 64;
        int m_DefaultRings = 32;

        float m_DefaultRotationSpeed = 16.0f;
        float m_DefaultPulseSpeed = 2.0f;
        float m_DefaultRimPower = 2.0f;
        float m_DefaultRimIntensity = 4.0f;

        SphereColorTheme m_DefaultColorTheme = SphereColorTheme::DeepSpace;

        glm::vec3 m_DefaultCameraPosition = glm::vec3(0.0f, 0.0f, 4.0f);
        glm::vec3 m_DefaultCameraRotation = glm::vec3(0.0f, 0.0f, 0.0f);

        void CreateSphere(float radius, unsigned int segments, unsigned int rings);
        void SetColorTheme(SphereColorTheme theme);
    };
}
