#include "view/camera.hpp"

namespace view
{
    using namespace glm;

    Camera::Camera(const vec3& position, const vec3& up, float yaw, float pitch)
        : m_Position(position),
          m_Front(vec3(0.0f, 0.0f, -1.0f)),
          m_Up(up),
          m_Right(vec3(1.0f, 0.0f, 0.0f)),
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

    mat4 Camera::GetViewMatrix() const
    {
        return lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    mat4 Camera::GetProjectionMatrix() const
    {
        return perspective(radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
    }

    void Camera::SetProjection(const float fov, const float aspect, const float near, const float far)
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

    void Camera::SetPosition(const vec3& position)
    {
        m_Position = position;
    }

    void Camera::SetRotation(float yaw, float pitch)
    {
        m_Yaw = yaw;
        m_Pitch = pitch;

        // Make sure that when pitch is out of bounds, the screen doesn't get flipped
        m_Pitch = clamp(m_Pitch, -89.0f, 89.0f);

        UpdateCameraVectors();
    }

    void Camera::UpdateCameraVectors()
    {
        // Calculate the new front vector
        vec3 front;

        front.x = cos(radians(m_Yaw)) * cos(radians(m_Pitch));
        front.y = sin(radians(m_Pitch));
        front.z = sin(radians(m_Yaw)) * cos(radians(m_Pitch));

        m_Front = normalize(front);

        // Re-calculate the right and up vector
        m_Right = normalize(cross(m_Front, m_WorldUp));
        m_Up = normalize(cross(m_Right, m_Front));
    }
}
