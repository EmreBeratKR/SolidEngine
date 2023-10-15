#include "engine_window.h"
#include "Rendering/vulkan_graphic_api.h";


int main() 
{
    Engine::EngineWindow window{800, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicApi graphicApi{window.getGLFWWindow()};

    window.setGraphicApi(&graphicApi);
    window.run();

    return 0;
}