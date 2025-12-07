#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace glm;
    using namespace scene;
    using namespace graphics;

    // Color theme options for wave plane
    enum class PlaneColorTheme
    {
        Unknown,
        AuroraSunset,      // Purple to orange (warm, magical)
        NeonCyberpunk,     // Magenta to cyan (electric, futuristic)
        OceanDepth,        // Deep blue to turquoise (calming)
        FireLava,          // Red to yellow (intense)
        MintRose,          // Pink to mint (soft, pastel)
        ToxicGreen,        // Lime to neon green (sci-fi)
        RoyalPurpleGold,   // Purple to gold (luxurious)
        CottonCandy,       // Pink to baby blue (sweet, dreamy)
        ElectricStorm,     // Electric blue to white (dramatic)
        PeachSunset,       // Coral to yellow (warm, cozy)
        MatrixGreen        // Matrix green gradient (digital)
    };

    class PlaneScene final : public Scene
    {
    public:
        // Constructor and Destructor
        PlaneScene();
        ~PlaneScene() override;

        // Scene lifecycle
        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        // Scene resources
        Mesh* m_PlaneMesh;
        Shader* m_Shader;

        // Transform matrices
        mat4 m_ModelMatrix;

        // Wave parameters
        int m_WaveCount;
        float m_Time;
        float m_WaveSpeed;
        float m_WaveAmplitude;
        float m_WaveFrequency;
        float m_OpacityFadeStart;

        // Grid properties
        int m_GridSize;

        // Plane properties
        float m_PlaneSize;
        float m_PlaneRadius;

        // Gradient colors
        Color m_CenterColor = Color::White;
        Color m_EdgeColor = Color::White;
        Color m_WavePeakColor = Color::White;
        Color m_WaveTroughColor = Color::White;
        PlaneColorTheme m_CurrentColorTheme = PlaneColorTheme::Unknown;

        // Mesh generation
        void CreatePlane(int gridSize, float planeSize);

        // Color management
        void SetColorTheme(PlaneColorTheme theme);
    };
}
