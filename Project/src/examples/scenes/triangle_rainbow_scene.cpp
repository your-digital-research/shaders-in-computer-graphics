#include <vector>

#include "view/camera.hpp"
#include "examples/scenes/triangle_rainbow_scene.hpp"

namespace examples
{
    using namespace std;
    using namespace glm;
    using namespace graphics;

    TriangleRainbowScene::TriangleRainbowScene()
        : m_TriangleMesh(nullptr),
          m_Shader(nullptr)
    {
        TriangleRainbowScene::OnCreate();
    }

    TriangleRainbowScene::~TriangleRainbowScene()
    {
        TriangleRainbowScene::OnDestroy();
    }

    void TriangleRainbowScene::OnCreate()
    {
        // Define vertices with positions and colors
        struct Vertex
        {
            vec3 position;
            vec3 color;
        };

        const vector<Vertex> vertices = {
            {vec3(0.0f, 0.5f, 0.0f), vec3(1.0f, 0.0f, 0.0f)}, // Top vertex (Red)
            {vec3(-0.5f, -0.5f, 0.0f), vec3(0.0f, 1.0f, 0.0f)}, // Bottom left (Green)
            {vec3(0.5f, -0.5f, 0.0f), vec3(0.0f, 0.0f, 1.0f)} // Bottom right (Blue)
        };

        // Extract positions and colors into separate vectors for our Mesh class
        vector<vec3> positions;
        vector<vec3> colors;

        for (const auto& [position, color] : vertices)
        {
            positions.push_back(position);
            colors.push_back(color);
        }

        // Create indices (though for a single triangle, we could draw without indices)
        const vector<unsigned int> indices = {0, 1, 2};

        // Create mesh and shader
        m_TriangleMesh = new Mesh(positions, indices, colors);
        m_Shader = new Shader("shaders/rainbow/vertex.glsl", "shaders/rainbow/fragment.glsl");

        // Setup camera
        m_Camera->SetPosition(vec3(0.0f, 0.0f, 3.0f));
        m_Camera->SetProjection(45.0f, 1.0f, 0.1f, 100.0f); // Aspect ratio will be updated by the engine
    }

    void TriangleRainbowScene::OnUpdate(float deltaTime)
    {
        // No updates needed for static triangle
    }

    void TriangleRainbowScene::OnRender()
    {
        // Bind shader and set uniforms
        m_Shader->Bind();
        m_Shader->SetMat4("uModel", mat4(1.0f)); // Identity matrix - no transformations
        m_Shader->SetMat4("uView", m_Camera->GetViewMatrix());
        m_Shader->SetMat4("uProjection", m_Camera->GetProjectionMatrix());

        // Render triangle
        m_TriangleMesh->Bind();
        m_TriangleMesh->Draw();

        Mesh::Unbind();
        Shader::Unbind();
    }

    void TriangleRainbowScene::OnDestroy()
    {
        delete m_TriangleMesh;
        delete m_Shader;

        m_TriangleMesh = nullptr;
        m_Shader = nullptr;
    }
}
