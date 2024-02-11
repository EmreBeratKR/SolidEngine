#include "engine_window.h"
#include "src/core/components/camera.h"
#include "src/core/game_object.h"
#include "src/core/components/transform.h"


int main() 
{
    Engine::EngineWindow window{600, 600, "Game Engine"};
    Engine::Rendering::VulkanGraphicEngine graphicEngine{&window};

    Engine::GameObject* cameraObject = new Engine::GameObject();
    cameraObject->getTransform()->position = glm::vec3(0.0f, 1.0f, -6.0f);
    Engine::Components::Camera* camera = Engine::Components::Camera::perspective(60.0f, 0.01f, 100.0f);
    camera->setGameObject(cameraObject);
    Engine::Components::Camera::main = camera;

    auto matrix = camera->getProjectionMatrix();
    std::cout << matrix[0][0] << "|" << matrix[0][1] << "|" << matrix[0][2] << "|" << matrix[0][3] << std::endl;
    std::cout << matrix[1][0] << "|" << matrix[1][1] << "|" << matrix[1][2] << "|" << matrix[1][3] << std::endl;
    std::cout << matrix[2][0] << "|" << matrix[2][1] << "|" << matrix[2][2] << "|" << matrix[2][3] << std::endl;
    std::cout << matrix[3][0] << "|" << matrix[3][1] << "|" << matrix[3][2] << "|" << matrix[3][3] << std::endl;

    window.setGraphicEngine(&graphicEngine);
    window.run();

    return EXIT_SUCCESS;
}