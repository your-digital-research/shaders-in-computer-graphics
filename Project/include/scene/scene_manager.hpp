#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "platform/window.hpp"
#include "scene/scene.hpp"

namespace scene
{
    using namespace std;
    using namespace platform;

    class SceneManager
    {
    public:
        // Constructor and Destructor
        explicit SceneManager(Window* window);
        ~SceneManager();

        // Initialization
        void InitializeDefaultScenes();

        // Scene management
        void AddScene(const string& name, unique_ptr<Scene> scene);
        void RemoveScene(const string& name);
        void SetActiveScene(const string& name);

        // Get the active scene
        [[nodiscard]] Scene* GetActiveScene() const { return m_ActiveScene; }
        [[nodiscard]] string GetActiveSceneName() const;
        [[nodiscard]] const unordered_map<string, unique_ptr<Scene>>& GetAllScenes() const { return m_Scenes; }

        // Update and render the active scene
        void UpdateActiveScene(float deltaTime) const;
        void RenderActiveScene() const;

    private:
        // Member variables
        Window* m_Window;
        Scene* m_ActiveScene;
        unordered_map<string, unique_ptr<Scene>> m_Scenes;
    };
}
