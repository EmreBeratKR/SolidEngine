#include <iostream>


#include "scene_manager.h"
#include "scene.h"
#include "game_object.h"
#include "camera.h"
#include "transform.h"
#include "mesh_renderer.h"
#include "model_loader.h"
#include "model.h"
#include "vulkan_buffer.h"
#include "vulkan_texture.h"
#include "vulkan_graphic_engine.h"
#include "time_api.h"
#include "input_api.h"


namespace Engine
{
	static Rendering::Model* model;
	static Rendering::Model* model1;
	static Rendering::VulkanTexture* texture;
	static Rendering::VulkanTexture* texture1;
	static float cameraPitch = 0.0f;
	static float cameraYaw = 0.0f;


	Scene::Scene()
	{
		SceneManager::activeScene = this;

		// Create camera
		auto cameraGameObject = new GameObject();
		auto camera = Components::Camera::perspective(60.0f, 0.01f, 100.0f);

		cameraGameObject->addComponent(camera);
		camera->getTransform()->position = {0.0f, 2.0f, -8.0f};

		Components::Camera::main = camera;

		// Create Texture
		texture = Rendering::VulkanTexture::Create("resources/textures/unity.png");
		texture1 = Rendering::VulkanTexture::Create("resources/textures/viking_room.png");

		// Create Model
		model = IO::loadObj("resources/models/monkey.obj");
		auto modelGameObject = new GameObject();
		auto meshRenderer = new Components::MeshRenderer();
		auto mesh = model->meshes[0];

		mesh->vertexBuffer->Allocate();
		mesh->indexBuffer->Allocate();
		modelGameObject->getTransform()->position = { 1.0f, 4.0f, 2.0f };
		modelGameObject->getTransform()->rotation = glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f)));
		modelGameObject->getTransform()->scale = { 1.0f, 1.0f, 1.0f };
		modelGameObject->addComponent(meshRenderer);
		meshRenderer->setMesh(mesh);

		// Create Model
		model1 = IO::loadObj("resources/models/cube.obj");
		auto modelGameObject1 = new GameObject();
		auto meshRenderer1 = new Components::MeshRenderer();
		auto mesh1 = model1->meshes[0];

		mesh1->vertexBuffer->Allocate();
		mesh1->indexBuffer->Allocate();
		modelGameObject1->getTransform()->position = { 1.0f, 0.0f, 2.0f };
		modelGameObject1->getTransform()->rotation = glm::quat(glm::radians(glm::vec3(0.0f, 0.0f, 0.0f)));
		modelGameObject1->getTransform()->scale = { 1.0f, 1.0f, 1.0f };
		modelGameObject1->addComponent(meshRenderer1);
		meshRenderer1->setMesh(mesh1);

		// Add GameObjects
		AddGameObject(cameraGameObject);
		AddGameObject(modelGameObject);
		AddGameObject(modelGameObject1);
	}

	Scene::~Scene()
	{
		for (const auto& gameObject : gameObjects)
		{
			delete gameObject;
		}

		delete model;
		delete model1;
	}


	void Scene::OnUpdate()
	{
		for (const auto& gameObject : gameObjects)
		{
			gameObject->OnUpdate();
		}

		// CAMERA CONTROL
		auto gameObject = gameObjects[0];
		auto transform = gameObject->getTransform();
		auto position = transform->position;
		auto rotation = transform->rotation;
		auto deltaPosition = glm::vec3 {0.0f};

		if (InputAPI::getKey(KeyCode::KEY_W))
		{
			deltaPosition += rotation * glm::vec3{0.0f, 0.0f, 1.0f};
		}

		if (InputAPI::getKey(KeyCode::KEY_S))
		{
			deltaPosition += rotation * glm::vec3{0.0f, 0.0f, -1.0f};
		}

		if (InputAPI::getKey(KeyCode::KEY_D))
		{
			deltaPosition += rotation * glm::vec3{1.0f, 0.0f, 0.0f};
		}

		if (InputAPI::getKey(KeyCode::KEY_A))
		{
			deltaPosition += rotation * glm::vec3{-1.0f, 0.0f, 0.0f};
		}

		if (InputAPI::getKey(KeyCode::KEY_E))
		{
			deltaPosition += rotation * glm::vec3{0.0f, 1.0f, 0.0f};
		}

		if (InputAPI::getKey(KeyCode::KEY_Q))
		{
			deltaPosition += rotation * glm::vec3{0.0f, -1.0f, 0.0f};
		}

		if (InputAPI::getKeyDown(KeyCode::KEY_ENTER))
		{
			InputAPI::setCursorLocked();
		}

		if (InputAPI::getKeyDown(KeyCode::KEY_ESCAPE))
		{
			InputAPI::setCursorNormal();
		}

		cameraPitch -= InputAPI::getMouseDeltaY() * TimeAPI::DeltaTime() * 10.0f;
		cameraYaw += InputAPI::getMouseDeltaX() * TimeAPI::DeltaTime() * 10.0f;

		if (cameraPitch > 90.0f)
		{
			cameraPitch = 90.0f;
		}

		else if (cameraPitch < -90.0f)
		{
			cameraPitch = -90.0f;
		}

		transform->position = position + (deltaPosition * (float) TimeAPI::DeltaTime() * 5.0f);
		transform->rotation = glm::quat(glm::radians(glm::vec3(cameraPitch, cameraYaw, 0.0f)));
		

		// SCENE

		auto targetGameObject = gameObjects[1];
		auto targetTransform = targetGameObject->getTransform();
		auto deltaAngle = 0.0f;

		if (InputAPI::getKey(KeyCode::KEY_RIGHT))
		{
			deltaAngle += 1.0f;
		}

		if (InputAPI::getKey(KeyCode::KEY_LEFT))
		{
			deltaAngle -= 1.0f;
		}

		targetTransform->rotation = targetTransform->rotation * glm::quat(glm::radians(glm::vec3(0.0f, deltaAngle * TimeAPI::DeltaTime() * 50.0f, 0.0f)));

		if (InputAPI::getKeyDown(KeyCode::KEY_SPACE))
		{
			Rendering::VulkanGraphicEngine::setTexture(1, texture);
		}

		if (InputAPI::getKeyUp(KeyCode::KEY_SPACE))
		{
			Rendering::VulkanGraphicEngine::setTexture(1, texture1);
		}
	}

	void Scene::OnRender()
	{
		auto camera = Components::Camera::main;
		auto view = camera->getViewMatrix();
		auto proj = camera->getProjectionMatrix();

		Rendering::VulkanGraphicEngine::setViewAndProjectionMatrices(view, proj);

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