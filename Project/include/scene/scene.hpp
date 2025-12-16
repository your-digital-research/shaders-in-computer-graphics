#pragma once

#include <string>

#include "view/camera.hpp"

namespace scene
{
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
