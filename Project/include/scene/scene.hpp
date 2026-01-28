#pragma once

#include <string>

#include "view/camera.hpp"

namespace scene
{
    using namespace view;

    class Scene
    {
    public:
        explicit Scene(Camera* camera);
        virtual ~Scene() = default;

        virtual void OnCreate() = 0;
        virtual void OnUpdate(float deltaTime) = 0;
        virtual void OnRender() = 0;
        virtual void OnDestroy() = 0;

        virtual void ResetToDefault() {}
        virtual void RenderSettings() {}

        [[nodiscard]] const std::string& GetName() const { return m_Name; }
        void SetName(const std::string& name) { m_Name = name; }

        [[nodiscard]] Camera* GetCamera() const { return m_Camera; }

        [[nodiscard]] virtual glm::vec3 GetDefaultCameraPosition() const { return {0.0f, 0.0f, 3.0f}; }
        [[nodiscard]] virtual glm::vec3 GetDefaultCameraRotation() const { return {0.0f, 0.0f, 0.0f}; }

    protected:
        std::string m_Name = "";
        Camera* m_Camera = nullptr;
    };
}
