#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "scene/scene.hpp"

namespace scene
{
    class SceneManager
    {
    public:
        SceneManager();
        ~SceneManager();

        // Add a scene to the manager
        void AddScene(const std::string& name, std::unique_ptr<Scene> scene);

        // Remove a scene from the manager
        void RemoveScene(const std::string& name);

        // Set the active scene
        void SetActiveScene(const std::string& name);

        // Get the active scene
        [[nodiscard]] Scene* GetActiveScene() const { return m_ActiveScene; }

        // Update and render the active scene
        void UpdateActiveScene(float deltaTime) const;
        void RenderActiveScene() const;

    private:
        std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
        Scene* m_ActiveScene;
    };
}
