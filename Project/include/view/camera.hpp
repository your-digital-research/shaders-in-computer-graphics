#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace view
{
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

        void SetPosition(const glm::vec3& position);
        void SetRotationEuler(const glm::vec3& eulerAngles);
        void SetRotationQuaternion(const glm::quat& quaternion);
        void Rotate(float pitch, float yaw, float roll);

        [[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
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

        [[nodiscard]] float GetYaw() const { return m_Yaw; }
        [[nodiscard]] float GetPitch() const { return m_Pitch; }
        [[nodiscard]] float GetRoll() const { return m_Roll; }

        [[nodiscard]] glm::vec3 GetEulerAngles() const { return {m_Pitch, m_Yaw, m_Roll}; }
        [[nodiscard]] glm::quat GetQuaternion() const { return m_Orientation; }

    private:
        glm::vec3 m_Position;

        glm::vec3 m_Front;
        glm::vec3 m_Back;
        glm::vec3 m_Up;
        glm::vec3 m_Down;
        glm::vec3 m_Right;
        glm::vec3 m_Left;

        glm::vec3 m_WorldFront;
        glm::vec3 m_WorldBack;
        glm::vec3 m_WorldUp;
        glm::vec3 m_WorldDown;
        glm::vec3 m_WorldRight;
        glm::vec3 m_WorldLeft;

        float m_Yaw;
        float m_Pitch;
        float m_Roll;

        glm::quat m_Orientation;

        float m_Fov;
        float m_AspectRatio;
        float m_NearPlane;
        float m_FarPlane;

        void UpdateCameraVectors();
        void UpdateQuaternionFromEuler();
        void UpdateEulerFromQuaternion();
    };
}
