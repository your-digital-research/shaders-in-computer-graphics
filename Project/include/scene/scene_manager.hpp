#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "platform/window.hpp"
#include "scene/scene.hpp"

namespace scene
{
    class SceneManager
    {
    public:
        // Constructor and Destructor
        explicit SceneManager(platform::Window* window);
        ~SceneManager();

        // Initialize default scenes
        void InitializeDefaultScenes();

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
        // Member variables
        std::unordered_map<std::string, std::unique_ptr<Scene>> m_Scenes;
        platform::Window* m_Window;
        Scene* m_ActiveScene;
    };
}
