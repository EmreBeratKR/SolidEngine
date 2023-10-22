#include "engine_window.h"


int main() 
{
    Engine::EngineWindow window{800, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicEngine graphicEngine{window.getGLFWWindow()};

    window.setGraphicApi(&graphicEngine);
    window.run();

    return EXIT_SUCCESS;
}