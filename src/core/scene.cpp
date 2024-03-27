#include <iostream>


#include "scene.h"
#include "scene_manager.h"
#include "game_object.h"
#include "components/transform.h"
#include "components/camera.h"
#include "components/mesh_renderer.h"
#include "../common/model_loader.h"
#include "rendering/vulkan_graphic_engine.h"


namespace Engine
{
	Scene::Scene()
	{
		SceneManager::activeScene = this;

		// Create camera
		auto cameraGameObject = new GameObject();
		auto camera = Components::Camera::perspective(60.0f, 0.01f, 100.0f);

		cameraGameObject->addComponent(camera);
		camera->getTransform()->position = {0.0f, 0.0f, -8.0f};

		Components::Camera::main = camera;

		// Create Model
		auto model = IO::loadObj("resources/models/viking_room.obj");
		auto modelGameObject = new GameObject();
		auto meshRenderer = new Components::MeshRenderer();

		modelGameObject->getTransform()->position = { 0.0f, -2.0f, 0.0f };
		modelGameObject->getTransform()->rotation = glm::quat(glm::radians(glm::vec3(10.0f, 225.0f, -10.0f)));
		modelGameObject->addComponent(meshRenderer);
		meshRenderer->setMesh(&model->meshes[0]);

		// Create Model
		auto model1 = IO::loadObj("resources/models/torus.obj");
		auto modelGameObject1 = new GameObject();
		auto meshRenderer1 = new Components::MeshRenderer();

		modelGameObject1->getTransform()->position = { 2.0f, -2.0f, 0.0f };
		modelGameObject1->getTransform()->rotation = glm::quat(glm::radians(glm::vec3(10.0f, 225.0f, -10.0f)));
		modelGameObject1->addComponent(meshRenderer1);
		meshRenderer1->setMesh(&model1->meshes[0]);

		// Add GameObjects
		AddGameObject(cameraGameObject);
		AddGameObject(modelGameObject);
		AddGameObject(modelGameObject1);
	}

	Scene::~Scene()
	{

	}


	void Scene::OnUpdate()
	{
		for (const auto& gameObject : gameObjects)
		{
			gameObject->OnUpdate();
		}
	}

	void Scene::OnRender()
	{
		auto camera = Components::Camera::main;
		auto view = camera->getViewMatrix();
		auto proj = camera->getProjectionMatrix();

		Rendering::VulkanGraphicEngine::ms_Instance->setViewAndProjectionMatrices(view, proj);

		for (const auto& gameObject : gameObjects)
		{
			gameObject->OnRender();
		}
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		gameObjects.push_back(gameObject);
	}
}