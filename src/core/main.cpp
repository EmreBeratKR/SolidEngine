#include "engine_window.h"
#include "src/core/components/camera.h"


int main() 
{
    Engine::EngineWindow window{600, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicEngine graphicEngine{&window};
    Engine::Components::Camera::main = Engine::Components::Camera::perspective(45.0f, 0.1f, 10.0f);

    window.setGraphicEngine(&graphicEngine);
    window.run();

    return EXIT_SUCCESS;
}