#pragma once

#include "scene/scene.hpp"
#include "graphics/mesh.hpp"
#include "graphics/shader.hpp"
#include "constants/math_constants.hpp"

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
        explicit PlaneScene(Camera* camera);
        ~PlaneScene() override;

        void OnCreate() override;
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnDestroy() override;

        void ResetToDefault() override;
        void RenderSettings() override;

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

        void SetPlaneSize(float planeSize);
        void SetGridSize(int gridSize);

        void SetOpacityFadeStart(float opacityStart);

        void SetWaveTroughColor(const Color& color);
        void SetWavePeakColor(const Color& color);
        void SetCenterColor(const Color& color);
        void SetEdgeColor(const Color& color);

    private:
        Mesh* m_Mesh = nullptr;
        Shader* m_Shader = nullptr;

        glm::mat4 m_ModelMatrix = glm::mat4(1.0f);

        int m_WaveCount = 8;
        float m_Time = 0.0f;
        float m_WaveSpeed = 5.0f;
        float m_WaveAmplitude = 0.25f;
        float m_WaveFrequency = constants::math::PI;
        float m_OpacityFadeStart = 0.5f;

        int m_GridSize = 128;
        float m_PlaneSize = 8.0f;
        float m_PlaneRadius = 0.0f;

        Color m_CenterColor = Color::White;
        Color m_EdgeColor = Color::White;
        Color m_WavePeakColor = Color::White;
        Color m_WaveTroughColor = Color::White;
        PlaneColorTheme m_CurrentColorTheme = PlaneColorTheme::NeonCyberpunk;

        float m_DefaultWaveSpeed = 5.0f;
        float m_DefaultWaveAmplitude = 0.25f;
        float m_DefaultWaveFrequency = constants::math::PI;
        float m_DefaultOpacityFadeStart = 0.5f;

        int m_DefaultGridSize = 128;
        float m_DefaultPlaneSize = 8.0f;

        PlaneColorTheme m_DefaultColorTheme = PlaneColorTheme::NeonCyberpunk;

        glm::vec3 m_DefaultCameraPosition = glm::vec3(0.0f, 7.5f, 8.25f);
        glm::vec3 m_DefaultCameraRotation = glm::vec3(-45.0f, 0.0f, 0.0f);

        void CreatePlane(int gridSize, float planeSize);
        void SetColorTheme(PlaneColorTheme theme);
    };
}
