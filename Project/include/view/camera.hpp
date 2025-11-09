#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace view
{
    class Camera
    {
    public:
        // Constructor and Destructor
        explicit Camera(
            const glm::vec3& position = glm::vec3(0.0f, 0.0f, 3.0f),
            const glm::vec3& up = glm::vec3(0.0f, 1.0f, 0.0f),
            float yaw = -90.0f,
            float pitch = 0.0f);
        ~Camera() = default;

        // Camera matrices
        [[nodiscard]] glm::mat4 GetViewMatrix() const;
        [[nodiscard]] glm::mat4 GetProjectionMatrix() const;

        // Camera properties
        void SetProjection(float fov, float aspect, float near, float far);
        void UpdateAspectRatio(float aspect);

        // Camera movement
        void SetPosition(const glm::vec3& position);
        void SetRotation(float yaw, float pitch);

        // Getters
        [[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
        [[nodiscard]] const glm::vec3& GetFront() const { return m_Front; }
        [[nodiscard]] const glm::vec3& GetUp() const { return m_Up; }
        [[nodiscard]] const glm::vec3& GetRight() const { return m_Right; }
        [[nodiscard]] float GetYaw() const { return m_Yaw; }
        [[nodiscard]] float GetPitch() const { return m_Pitch; }

    private:
        // Camera attributes
        glm::vec3 m_Position;
        glm::vec3 m_Front;
        glm::vec3 m_Up;
        glm::vec3 m_Right;
        glm::vec3 m_WorldUp;

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
