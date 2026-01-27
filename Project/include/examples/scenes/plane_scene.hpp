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

        void RenderSettings() override;
        void ResetToDefault() override;

        [[nodiscard]] glm::vec3 GetDefaultCameraPosition() const override { return m_DefaultCameraPosition; }
        [[nodiscard]] glm::vec3 GetDefaultCameraRotation() const override { return m_DefaultCameraRotation; }

        [[nodiscard]] float GetWaveSpeed() const { return m_WaveSpeed; }
        [[nodiscard]] float GetWaveAmplitude() const { return m_WaveAmplitude; }
        [[nodiscard]] float GetWaveFrequency() const { return m_WaveFrequency; }
        [[nodiscard]] float GetOpacityFadeStart() const { return m_OpacityFadeStart; }
        [[nodiscard]] int GetGridSize() const { return m_GridSize; }
        [[nodiscard]] float GetPlaneSize() const { return m_PlaneSize; }
        [[nodiscard]] float GetPlaneRadius() const { return m_PlaneRadius; }

        void SetWaveSpeed(float speed);
        void SetWaveAmplitude(float amplitude);
        void SetWaveFrequency(float frequency);
        void SetOpacityFadeStart(float opacityStart);
        void SetGridSize(int gridSize);
        void SetPlaneSize(float planeSize);

        void SetCenterColor(const Color& color);
        void SetEdgeColor(const Color& color);
        void SetWavePeakColor(const Color& color);
        void SetWaveTroughColor(const Color& color);

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

        int m_DefaultGridSize;
        float m_DefaultPlaneSize;
        float m_DefaultWaveSpeed;
        float m_DefaultWaveAmplitude;
        float m_DefaultWaveFrequency;
        float m_DefaultOpacityFadeStart;

        PlaneColorTheme m_DefaultColorTheme;

        glm::vec3 m_DefaultCameraPosition;
        glm::vec3 m_DefaultCameraRotation;

        void CreatePlane(int gridSize, float planeSize);
        void SetColorTheme(PlaneColorTheme theme);
    };
}
