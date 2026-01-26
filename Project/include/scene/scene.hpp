#pragma once

#include <string>

#include "view/camera.hpp"

namespace scene
{
    using namespace glm;
    using namespace std;
    using namespace view;

    class Scene
    {
    public:
        Scene();
        virtual ~Scene() = default;

        virtual void OnCreate() = 0;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnRender() = 0;
        virtual void OnDestroy() = 0;

        virtual void RenderSettings() {}
        virtual void ResetToDefault() {}

        [[nodiscard]] vec3 GetCameraPosition() const
        {
            return m_Camera ? m_Camera->GetPosition() : vec3(0.0f);
        }
        [[nodiscard]] vec3 GetCameraRotation() const
        {
            return m_Camera ? m_Camera->GetEulerAngles() : vec3(0.0f);
        }

        void SetCameraPosition(const vec3& position) const
        {
            if (m_Camera) m_Camera->SetPosition(position);
        }
        void SetCameraRotation(const vec3& rotation) const
        {
            if (m_Camera) m_Camera->SetRotationEuler(rotation);
        }

        [[nodiscard]] virtual vec3 GetDefaultCameraPosition() const { return {0.0f, 0.0f, 3.0f}; }
        [[nodiscard]] virtual vec3 GetDefaultCameraRotation() const { return {0.0f, 0.0f, 0.0f}; }

        void UpdateAspectRatio(const float aspect) const
        {
            if (m_Camera) m_Camera->UpdateAspectRatio(aspect);
        }

        [[nodiscard]] const string& GetName() const { return m_Name; }
        void SetName(const string& name) { m_Name = name; }

    protected:
        string m_Name;
        Camera* m_Camera;
    };
}
