#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace view
{
    using namespace glm;

    class Camera
    {
    public:
        // Constructor and Destructor
        explicit Camera(
            const vec3& position = vec3(0.0f, 0.0f, 3.0f),
            const vec3& up = vec3(0.0f, 1.0f, 0.0f),
            float pitch = 0.0f,
            float yaw = 0.0f,
            float roll = 0.0f);
        ~Camera() = default;

        // Camera matrices
        [[nodiscard]] mat4 GetViewMatrix() const;
        [[nodiscard]] mat4 GetProjectionMatrix() const;

        // Camera properties
        void SetProjection(float fov, float aspect, float near, float far);
        void UpdateAspectRatio(float aspect);

        // Camera movement and rotation
        void SetPosition(const vec3& position);
        void SetRotationEuler(const vec3& eulerAngles);
        void SetRotationQuaternion(const quat& quaternion);
        void Rotate(float pitch, float yaw, float roll);

        // Getters - Position
        [[nodiscard]] const vec3& GetPosition() const { return m_Position; }

        // Getters - Camera directional vectors
        [[nodiscard]] const vec3& GetFront() const { return m_Front; }
        [[nodiscard]] const vec3& GetBack() const { return m_Back; }
        [[nodiscard]] const vec3& GetUp() const { return m_Up; }
        [[nodiscard]] const vec3& GetDown() const { return m_Down; }
        [[nodiscard]] const vec3& GetRight() const { return m_Right; }
        [[nodiscard]] const vec3& GetLeft() const { return m_Left; }

        // Getters - World directional vectors
        [[nodiscard]] const vec3& GetWorldFront() const { return m_WorldFront; }
        [[nodiscard]] const vec3& GetWorldBack() const { return m_WorldBack; }
        [[nodiscard]] const vec3& GetWorldUp() const { return m_WorldUp; }
        [[nodiscard]] const vec3& GetWorldDown() const { return m_WorldDown; }
        [[nodiscard]] const vec3& GetWorldRight() const { return m_WorldRight; }
        [[nodiscard]] const vec3& GetWorldLeft() const { return m_WorldLeft; }

        // Getters - Euler angles
        [[nodiscard]] float GetYaw() const { return m_Yaw; }
        [[nodiscard]] float GetPitch() const { return m_Pitch; }
        [[nodiscard]] float GetRoll() const { return m_Roll; }
        [[nodiscard]] vec3 GetEulerAngles() const { return {m_Yaw, m_Pitch, m_Roll}; }

        // Getters - Quaternion
        [[nodiscard]] quat GetQuaternion() const { return m_Orientation; }

    private:
        // Camera position
        vec3 m_Position;

        // Camera local directional vectors
        vec3 m_Front;
        vec3 m_Back;
        vec3 m_Up;
        vec3 m_Down;
        vec3 m_Right;
        vec3 m_Left;

        // World directional vectors
        vec3 m_WorldFront;
        vec3 m_WorldBack;
        vec3 m_WorldUp;
        vec3 m_WorldDown;
        vec3 m_WorldRight;
        vec3 m_WorldLeft;

        // Euler angles (in degrees)
        float m_Yaw;
        float m_Pitch;
        float m_Roll;

        // Quaternion orientation
        quat m_Orientation;

        // Projection parameters
        float m_Fov;
        float m_AspectRatio;
        float m_NearPlane;
        float m_FarPlane;

        // Utility functions
        void UpdateCameraVectors();
        void UpdateQuaternionFromEuler();
        void UpdateEulerFromQuaternion();
    };
}
