#include "application.h"
#include "rendering/vulkan_graphic_engine.h"
#include "scene.h"


int main() 
{
    Engine::Application application{600, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicEngine graphicEngine{&application};

    Engine::Scene scene;

    application.PushLayer(&graphicEngine);
    application.run();

    return EXIT_SUCCESS;
}