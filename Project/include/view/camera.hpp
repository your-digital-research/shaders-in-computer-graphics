#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace view
{
    using namespace glm;

    class Camera
    {
    public:
        explicit Camera(
            const vec3& position = vec3(0.0f, 0.0f, 3.0f),
            const vec3& up = vec3(0.0f, 1.0f, 0.0f),
            float pitch = 0.0f,
            float yaw = 0.0f,
            float roll = 0.0f);
        ~Camera() = default;

        [[nodiscard]] mat4 GetViewMatrix() const;
        [[nodiscard]] mat4 GetProjectionMatrix() const;

        void SetProjection(float fov, float aspect, float near, float far);
        void UpdateAspectRatio(float aspect);

        void SetPosition(const vec3& position);
        void SetRotationEuler(const vec3& eulerAngles);
        void SetRotationQuaternion(const quat& quaternion);
        void Rotate(float pitch, float yaw, float roll);

        [[nodiscard]] const vec3& GetPosition() const { return m_Position; }
        [[nodiscard]] const vec3& GetFront() const { return m_Front; }
        [[nodiscard]] const vec3& GetBack() const { return m_Back; }
        [[nodiscard]] const vec3& GetUp() const { return m_Up; }
        [[nodiscard]] const vec3& GetDown() const { return m_Down; }
        [[nodiscard]] const vec3& GetRight() const { return m_Right; }
        [[nodiscard]] const vec3& GetLeft() const { return m_Left; }
        [[nodiscard]] const vec3& GetWorldFront() const { return m_WorldFront; }
        [[nodiscard]] const vec3& GetWorldBack() const { return m_WorldBack; }
        [[nodiscard]] const vec3& GetWorldUp() const { return m_WorldUp; }
        [[nodiscard]] const vec3& GetWorldDown() const { return m_WorldDown; }
        [[nodiscard]] const vec3& GetWorldRight() const { return m_WorldRight; }
        [[nodiscard]] const vec3& GetWorldLeft() const { return m_WorldLeft; }

        [[nodiscard]] float GetYaw() const { return m_Yaw; }
        [[nodiscard]] float GetPitch() const { return m_Pitch; }
        [[nodiscard]] float GetRoll() const { return m_Roll; }

        [[nodiscard]] vec3 GetEulerAngles() const { return {m_Yaw, m_Pitch, m_Roll}; }
        [[nodiscard]] quat GetQuaternion() const { return m_Orientation; }

    private:
        vec3 m_Position;

        vec3 m_Front;
        vec3 m_Back;
        vec3 m_Up;
        vec3 m_Down;
        vec3 m_Right;
        vec3 m_Left;

        vec3 m_WorldFront;
        vec3 m_WorldBack;
        vec3 m_WorldUp;
        vec3 m_WorldDown;
        vec3 m_WorldRight;
        vec3 m_WorldLeft;

        float m_Yaw;
        float m_Pitch;
        float m_Roll;

        quat m_Orientation;

        float m_Fov;
        float m_AspectRatio;
        float m_NearPlane;
        float m_FarPlane;

        void UpdateCameraVectors();
        void UpdateQuaternionFromEuler();
        void UpdateEulerFromQuaternion();
    };
}
