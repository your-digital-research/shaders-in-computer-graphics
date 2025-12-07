#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace glm;
    using namespace scene;
    using namespace graphics;

    // Color theme options for a sphere
    enum class SphereColorTheme
    {
        Unknown,
        CyberGlow,         // Cyan to purple (cyberpunk)
        FireBall,          // Red to yellow (intense)
        IceSphere,         // Light blue to deep blue (frozen)
        NeonPink,          // Hot pink to magenta (electric)
        EnergyShield,      // Green to lime (sci-fi)
        AuroraBorealis,    // Purple to cyan (mystical)
        SunsetGlow,        // Orange to pink (warm)
        ToxicWaste,        // Yellow to lime (radioactive)
        DeepSpace,         // Dark purple to white (cosmic)
        HologramBlue       // Electric blue to white (futuristic)
    };

    class SphereScene final : public Scene
    {
    public:
        // Constructor and Destructor
        SphereScene();
        ~SphereScene() override;

        // Scene lifecycle
        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        // Scene resources
        Mesh* m_SphereMesh;
        Shader* m_Shader;

        // Transform matrices
        mat4 m_ModelMatrix;

        // Animation parameters
        float m_RotationAngle;
        float m_RotationSpeed;
        float m_PulseSpeed;
        float m_Time;

        // Sphere properties
        float m_SphereRadius;
        int m_Segments;
        int m_Rings;

        // Fresnel / Rim parameters
        float m_RimPower;
        float m_RimIntensity;

        // Colors
        Color m_RimColor = Color::White;
        Color m_CoreColor = Color::White;
        SphereColorTheme m_CurrentColorTheme = SphereColorTheme::Unknown;

        // Mesh generation
        void CreateSphere(float radius, unsigned int segments, unsigned int rings);

        // Color management
        void SetColorTheme(SphereColorTheme theme);
    };
}
