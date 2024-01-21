#include "engine_window.h"
#include "src/core/components/camera.h"
#include "src/core/game_object.h"
#include "src/core/components/transform.h"


int main() 
{
    Engine::EngineWindow window{600, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicEngine graphicEngine{&window};

    Engine::GameObject* cameraObject = new Engine::GameObject();
    cameraObject->getTransform()->position = glm::vec3(2.0f, 2.0f, 2.0f);
    Engine::Components::Camera* camera = Engine::Components::Camera::perspective(45.0f, 0.1f, 10.0f);
    camera->setGameObject(cameraObject);
    Engine::Components::Camera::main = camera;

    window.setGraphicEngine(&graphicEngine);
    window.run();

    return EXIT_SUCCESS;
}