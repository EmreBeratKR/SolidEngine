#include "application.h"
#include "rendering/vulkan_graphic_engine.h"
#include "scene_manager.h"
#include "scene.h"


int main() 
{
    Engine::Application application{600, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicEngine graphicEngine{&application};
    Engine::SceneManager sceneManager{};

    Engine::Scene scene;

    application.PushLayer(&sceneManager);
    application.run();

    return EXIT_SUCCESS;
}