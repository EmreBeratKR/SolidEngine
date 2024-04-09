#define GLFW_INCLUDE_VULKAN


#include "application.h"
#include "vulkan_graphic_engine.h"
#include "scene_manager.h"
#include "scene.h"
#include "time_api.h"


int main() 
{
    Engine::TimeAPI timeApi;
    Engine::Application application{600, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicEngine graphicEngine{&application};
    Engine::SceneManager sceneManager;

    Engine::Scene scene;

    application.pushLayer(&timeApi);
    application.pushLayer(&sceneManager);
    application.run();

    return EXIT_SUCCESS;
}