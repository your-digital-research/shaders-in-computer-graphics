#include "view/camera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace view
{
    Camera::Camera(const glm::vec3& position, const glm::vec3& up, const float pitch, const float yaw, const float roll)
        : m_Position(position),
          m_Up(up),
          m_Down(-up),
          m_WorldUp(up),
          m_WorldDown(-up),
          m_Yaw(yaw),
          m_Pitch(pitch),
          m_Roll(roll)
    {
        UpdateCameraVectors();
    }

    glm::mat4 Camera::GetViewMatrix() const
    {
        return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
    }

    glm::mat4 Camera::GetProjectionMatrix() const
    {
        switch (m_ProjectionType)
        {
            case ProjectionType::Perspective:
                return GetPerspectiveProjectionMatrix();

            case ProjectionType::Orthographic:
                return GetOrthographicProjectionMatrix();

            default:
                return GetPerspectiveProjectionMatrix();
        }
    }

    glm::mat4 Camera::GetPerspectiveProjectionMatrix() const
    {
        return glm::perspective(glm::radians(m_Fov), m_AspectRatio, m_NearPlane, m_FarPlane);
    }

    glm::mat4 Camera::GetOrthographicProjectionMatrix() const
    {
        // For orthographic projection, calculate the visible area based on an aspect ratio
        constexpr float height = 5.0f; // Fixed orthographic height
        const float width = height * m_AspectRatio;

        return glm::ortho(-width / 2.0f, width / 2.0f, -height / 2.0f, height / 2.0f, m_NearPlane, m_FarPlane);
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

    void Camera::SetPosition(const glm::vec3& position)
    {
        m_Position = position;
    }

    void Camera::SetRotationEuler(const glm::vec3& eulerAngles)
    {
        m_Pitch = eulerAngles.x;
        m_Yaw = eulerAngles.y;
        m_Roll = eulerAngles.z;

        m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

        UpdateCameraVectors();
    }

    void Camera::SetRotationQuaternion(const glm::quat& quaternion)
    {
        m_Orientation = glm::normalize(quaternion);

        UpdateEulerFromQuaternion();
        UpdateCameraVectors();
    }

    void Camera::Rotate(const float pitch, const float yaw, const float roll)
    {
        m_Pitch += pitch;
        m_Yaw += yaw;
        m_Roll += roll;

        // Clamp pitch to prevent gimbal lock
        m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

        // Normalize yaw and roll to [-180, 180]
        while (m_Yaw > 180.0f) m_Yaw -= 360.0f;
        while (m_Yaw < -180.0f) m_Yaw += 360.0f;
        while (m_Roll > 180.0f) m_Roll -= 360.0f;
        while (m_Roll < -180.0f) m_Roll += 360.0f;

        UpdateCameraVectors();
    }

    void Camera::UpdateCameraVectors()
    {
        // Calculate front vector from Euler angles
        glm::vec3 front;

        front.x = glm::sin(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));
        front.y = glm::sin(glm::radians(m_Pitch));
        front.z = -glm::cos(glm::radians(m_Yaw)) * glm::cos(glm::radians(m_Pitch));

        m_Front = glm::normalize(front);
        m_Back = -m_Front;

        // Calculate right vector
        m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));

        // Calculate up vector considering roll
        const glm::vec3 baseUp = glm::normalize(glm::cross(m_Right, m_Front));

        // Apply roll rotation around the front axis
        if (glm::abs(m_Roll) > 0.001f)
        {
            const glm::quat rollQuat = glm::angleAxis(glm::radians(m_Roll), m_Front);

            m_Up = glm::normalize(rollQuat * baseUp);
            m_Right = glm::normalize(glm::cross(m_Front, m_Up));
        }
        else
        {
            m_Up = baseUp;
        }

        // Calculate left and down vectors
        m_Left = -m_Right;
        m_Down = -m_Up;

        // Update quaternion from Euler angles
        UpdateQuaternionFromEuler();
    }

    void Camera::UpdateQuaternionFromEuler()
    {
        // Convert Euler angles to quaternion (YXZ order: Yaw-Pitch-Roll)
        const glm::quat qYaw = glm::angleAxis(glm::radians(m_Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
        const glm::quat qPitch = glm::angleAxis(glm::radians(m_Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
        const glm::quat qRoll = glm::angleAxis(glm::radians(m_Roll), glm::vec3(0.0f, 0.0f, 1.0f));

        m_Orientation = glm::normalize(qYaw * qPitch * qRoll);
    }

    void Camera::UpdateEulerFromQuaternion()
    {
        // Convert quaternion to Euler angles
        const glm::vec3 euler = eulerAngles(m_Orientation);

        m_Pitch = glm::degrees(euler.x);
        m_Yaw = glm::degrees(euler.y);
        m_Roll = glm::degrees(euler.z);

        // Clamp pitch
        m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);
    }
}
