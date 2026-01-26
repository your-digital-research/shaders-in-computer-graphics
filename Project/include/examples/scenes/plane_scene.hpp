#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"

namespace examples
{
    using namespace scene;
    using namespace graphics;

    enum class PlaneColorTheme
    {
        Unknown,
        AuroraSunset,
        NeonCyberpunk,
        OceanDepth,
        FireLava,
        MintRose,
        ToxicGreen,
        RoyalPurpleGold,
        CottonCandy,
        ElectricStorm,
        PeachSunset,
        MatrixGreen
    };

    class PlaneScene final : public Scene
    {
    public:
        PlaneScene();
        ~PlaneScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

    private:
        Mesh* m_PlaneMesh;
        Shader* m_Shader;

        glm::mat4 m_ModelMatrix;

        int m_WaveCount;
        float m_Time;
        float m_WaveSpeed;
        float m_WaveAmplitude;
        float m_WaveFrequency;
        float m_OpacityFadeStart;

        int m_GridSize;
        float m_PlaneSize;
        float m_PlaneRadius;

        Color m_CenterColor = Color::White;
        Color m_EdgeColor = Color::White;
        Color m_WavePeakColor = Color::White;
        Color m_WaveTroughColor = Color::White;
        PlaneColorTheme m_CurrentColorTheme = PlaneColorTheme::Unknown;

        void CreatePlane(int gridSize, float planeSize);
        void SetColorTheme(PlaneColorTheme theme);
    };
}
