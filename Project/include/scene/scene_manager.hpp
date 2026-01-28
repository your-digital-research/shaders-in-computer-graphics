#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "platform/window.hpp"
#include "scene/scene.hpp"
#include "view/camera.hpp"

namespace scene
{
    using namespace platform;
    using namespace view;

    class SceneManager
    {
    public:
        explicit SceneManager(Window* window);
        ~SceneManager();

        void InitializeDefaultScenes();

        void AddScene(const std::string& name, std::unique_ptr<Scene> scene);
        void RemoveScene(const std::string& name);
        void SetActiveScene(const std::string& name);

        [[nodiscard]] Camera* GetCamera() const { return m_Camera.get(); }

        [[nodiscard]] Scene* GetActiveScene() const { return m_ActiveScene; }
        [[nodiscard]] std::string GetActiveSceneName() const;
        [[nodiscard]] const std::unordered_map<std::string, std::unique_ptr<Scene>>& GetAllScenes() const { return m_Scenes; }

        void UpdateActiveScene(float deltaTime) const;
        void RenderActiveScene() const;

    private:
        Window* m_Window = nullptr;
        Scene* m_ActiveScene = nullptr;

        std::unique_ptr<Camera> m_Camera;
        std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
    };
}
