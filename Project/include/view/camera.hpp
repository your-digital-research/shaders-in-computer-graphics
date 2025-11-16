#pragma once

#include <glm/glm.hpp>
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
            float yaw = -90.0f,
            float pitch = 0.0f);
        ~Camera() = default;

        // Camera matrices
        [[nodiscard]] mat4 GetViewMatrix() const;
        [[nodiscard]] mat4 GetProjectionMatrix() const;

        // Camera properties
        void SetProjection(float fov, float aspect, float near, float far);
        void UpdateAspectRatio(float aspect);

        // Camera movement
        void SetPosition(const vec3& position);
        void SetRotation(float yaw, float pitch);

        // Getters
        [[nodiscard]] const vec3& GetPosition() const { return m_Position; }
        [[nodiscard]] const vec3& GetFront() const { return m_Front; }
        [[nodiscard]] const vec3& GetUp() const { return m_Up; }
        [[nodiscard]] const vec3& GetRight() const { return m_Right; }
        [[nodiscard]] float GetYaw() const { return m_Yaw; }
        [[nodiscard]] float GetPitch() const { return m_Pitch; }

    private:
        // Camera attributes
        vec3 m_Position;
        vec3 m_Front;
        vec3 m_Up;
        vec3 m_Right;
        vec3 m_WorldUp;

        // Euler angles
        float m_Yaw;
        float m_Pitch;

        // Projection parameters
        float m_Fov;
        float m_AspectRatio;
        float m_NearPlane;
        float m_FarPlane;

        // Utility function
        void UpdateCameraVectors();
    };
}
