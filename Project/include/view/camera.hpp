#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include "constants/graphics_constants.hpp"

namespace view
{
    enum class ProjectionType
    {
        Perspective,
        Orthographic
    };

    class Camera
    {
    public:
        explicit Camera(
            const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
            const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
            float pitch = 0.0f,
            float yaw = 0.0f,
            float roll = 0.0f);
        ~Camera() = default;

        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

        void SetProjection(float fov, float aspect, float near, float far);
        void UpdateAspectRatio(float aspect);

        void SetProjectionType(const ProjectionType type) { m_ProjectionType = type; }
        [[nodiscard]] ProjectionType GetProjectionType() const { return m_ProjectionType; }

        void SetFov(const float fov) { m_Fov = fov; }
        [[nodiscard]] float GetFov() const { return m_Fov; }

        void SetNearPlane(const float near) { m_NearPlane = near; }
        [[nodiscard]] float GetNearPlane() const { return m_NearPlane; }

        void SetFarPlane(const float far) { m_FarPlane = far; }
        [[nodiscard]] float GetFarPlane() const { return m_FarPlane; }

        void SetPosition(const glm::vec3& position);
        [[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }

        void SetRotationEuler(const glm::vec3& eulerAngles);
        [[nodiscard]] glm::vec3 GetEulerAngles() const { return {m_Pitch, m_Yaw, m_Roll}; }

        void SetRotationQuaternion(const glm::quat& quaternion);
        [[nodiscard]] glm::quat GetQuaternion() const { return m_Orientation; }

        void Rotate(float pitch, float yaw, float roll);

        [[nodiscard]] float GetYaw() const { return m_Yaw; }
        [[nodiscard]] float GetPitch() const { return m_Pitch; }
        [[nodiscard]] float GetRoll() const { return m_Roll; }

        [[nodiscard]] const glm::vec3& GetFront() const { return m_Front; }
        [[nodiscard]] const glm::vec3& GetBack() const { return m_Back; }
        [[nodiscard]] const glm::vec3& GetUp() const { return m_Up; }
        [[nodiscard]] const glm::vec3& GetDown() const { return m_Down; }
        [[nodiscard]] const glm::vec3& GetRight() const { return m_Right; }
        [[nodiscard]] const glm::vec3& GetLeft() const { return m_Left; }
        [[nodiscard]] const glm::vec3& GetWorldFront() const { return m_WorldFront; }
        [[nodiscard]] const glm::vec3& GetWorldBack() const { return m_WorldBack; }
        [[nodiscard]] const glm::vec3& GetWorldUp() const { return m_WorldUp; }
        [[nodiscard]] const glm::vec3& GetWorldDown() const { return m_WorldDown; }
        [[nodiscard]] const glm::vec3& GetWorldRight() const { return m_WorldRight; }
        [[nodiscard]] const glm::vec3& GetWorldLeft() const { return m_WorldLeft; }

    private:
        glm::vec3 m_Position = glm::vec3(0.0f, 0.0f, 3.0f);

        glm::vec3 m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_Back = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_Down = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 m_Right = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_Left = glm::vec3(-1.0f, 0.0f, 0.0f);

        glm::vec3 m_WorldFront = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_WorldBack = glm::vec3(0.0f, 0.0f, 1.0f);
        glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
        glm::vec3 m_WorldDown = glm::vec3(0.0f, -1.0f, 0.0f);
        glm::vec3 m_WorldRight = glm::vec3(1.0f, 0.0f, 0.0f);
        glm::vec3 m_WorldLeft = glm::vec3(-1.0f, 0.0f, 0.0f);

        float m_Yaw = 0.0f;
        float m_Pitch = 0.0f;
        float m_Roll = 0.0f;

        glm::quat m_Orientation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);

        ProjectionType m_ProjectionType = ProjectionType::Perspective;

        float m_Fov = constants::graphics::DEFAULT_FOV;
        float m_AspectRatio = 1.0f;
        float m_NearPlane = constants::graphics::DEFAULT_NEAR_PLANE;
        float m_FarPlane = constants::graphics::DEFAULT_FAR_PLANE;

        [[nodiscard]] glm::mat4 GetPerspectiveProjectionMatrix() const;
        [[nodiscard]] glm::mat4 GetOrthographicProjectionMatrix() const;

        void UpdateCameraVectors();
        void UpdateQuaternionFromEuler();
        void UpdateEulerFromQuaternion();
    };
}
