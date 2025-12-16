#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "constants/graphics_constants.hpp"
#include "view/camera.hpp"

namespace view
{
    using namespace glm;

    Camera::Camera(const vec3& position, const vec3& up, const float pitch, const float yaw, const float roll)
        : m_Position(position),
          m_Front(vec3(0.0f, 0.0f, -1.0f)),
          m_Back(vec3(0.0f, 0.0f, 1.0f)),
          m_Up(up),
          m_Down(-up),
          m_Right(vec3(1.0f, 0.0f, 0.0f)),
          m_Left(vec3(-1.0f, 0.0f, 0.0f)),
          m_WorldFront(vec3(0.0f, 0.0f, -1.0f)),
          m_WorldBack(vec3(0.0f, 0.0f, 1.0f)),
          m_WorldUp(up),
          m_WorldDown(-up),
          m_WorldRight(vec3(1.0f, 0.0f, 0.0f)),
          m_WorldLeft(vec3(-1.0f, 0.0f, 0.0f)),
          m_Yaw(yaw),
          m_Pitch(pitch),
          m_Roll(roll),
          m_Orientation(quat(1.0f, 0.0f, 0.0f, 0.0f)),
          m_Fov(constants::graphics::DEFAULT_FOV),
          m_AspectRatio(1.0f),
          m_NearPlane(constants::graphics::DEFAULT_NEAR_PLANE),
          m_FarPlane(constants::graphics::DEFAULT_FAR_PLANE)
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

    void Camera::SetRotationEuler(const vec3& eulerAngles)
    {
        m_Pitch = eulerAngles.x;
        m_Yaw = eulerAngles.y;
        m_Roll = eulerAngles.z;

        m_Pitch = clamp(m_Pitch, -89.0f, 89.0f);

        UpdateCameraVectors();
    }

    void Camera::SetRotationQuaternion(const quat& quaternion)
    {
        m_Orientation = normalize(quaternion);

        UpdateEulerFromQuaternion();
        UpdateCameraVectors();
    }

    void Camera::Rotate(const float pitch, const float yaw, const float roll)
    {
        m_Pitch += pitch;
        m_Yaw += yaw;
        m_Roll += roll;

        // Clamp pitch to prevent gimbal lock
        m_Pitch = clamp(m_Pitch, -89.0f, 89.0f);

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
        vec3 front;

        front.x = sin(radians(m_Yaw)) * cos(radians(m_Pitch));
        front.y = sin(radians(m_Pitch));
        front.z = -cos(radians(m_Yaw)) * cos(radians(m_Pitch));

        m_Front = normalize(front);
        m_Back = -m_Front;

        // Calculate right vector
        m_Right = normalize(cross(m_Front, m_WorldUp));

        // Calculate up vector considering roll
        const vec3 baseUp = normalize(cross(m_Right, m_Front));

        // Apply roll rotation around the front axis
        if (abs(m_Roll) > 0.001f)
        {
            const quat rollQuat = angleAxis(radians(m_Roll), m_Front);

            m_Up = normalize(rollQuat * baseUp);
            m_Right = normalize(cross(m_Front, m_Up));
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
        const quat qYaw = angleAxis(radians(m_Yaw), vec3(0.0f, 1.0f, 0.0f));
        const quat qPitch = angleAxis(radians(m_Pitch), vec3(1.0f, 0.0f, 0.0f));
        const quat qRoll = angleAxis(radians(m_Roll), vec3(0.0f, 0.0f, 1.0f));

        m_Orientation = normalize(qYaw * qPitch * qRoll);
    }

    void Camera::UpdateEulerFromQuaternion()
    {
        // Convert quaternion to Euler angles
        const vec3 euler = eulerAngles(m_Orientation);

        m_Pitch = degrees(euler.x);
        m_Yaw = degrees(euler.y);
        m_Roll = degrees(euler.z);

        // Clamp pitch
        m_Pitch = clamp(m_Pitch, -89.0f, 89.0f);
    }
}
