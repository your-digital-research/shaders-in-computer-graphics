#include "view/camera.hpp"

namespace view
{
    Camera::Camera(const glm::vec3& position, const glm::vec3& up, float yaw, float pitch)
        : m_Position(position),
          m_Front(glm::vec3(0.0f, 0.0f, -1.0f)),
          m_WorldUp(up),
          m_Yaw(yaw),
          m_Pitch(pitch),
          m_Fov(45.0f),
          m_AspectRatio(1.0f),
          m_NearPlane(0.1f),
          m_FarPlane(100.0f)
    {
        UpdateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        return glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
    }

    void Camera::SetProjection(float fov, float aspect, float near, float far)
    {
        m_Fov = fov;
        m_AspectRatio = aspect;
        m_NearPlane = near;
        m_FarPlane = far;
    }

    void Camera::UpdateAspectRatio(const float aspect)
    {
        m_AspectRatio = aspect;
    }

    void Camera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
    }

    void Camera::SetRotation(float yaw, float pitch)
    {
        m_Yaw = yaw;
        m_Pitch = pitch;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
        m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

        UpdateCameraVectors();
    }

    void Camera::UpdateCameraVectors()
    {
        // Calculate the new front vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        front.y = sin(glm::radians(m_Pitch));
        front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
        m_Front = glm::normalize(front);

        // Re-calculate the right and up vector
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
        m_Up = glm::normalize(glm::cross(m_Right, m_Front));
    }
}
