#include "engine_window.h"


int main() 
{
    Engine::EngineWindow window{800, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicEngine graphicEngine{&window};

    window.setGraphicEngine(&graphicEngine);
    window.run();

    return EXIT_SUCCESS;
}