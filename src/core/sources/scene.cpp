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
#include "vulkan_graphic_engine.h"
#include "time_api.h"
#include "input.api.h"


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
		auto mesh = model->meshes[0];

		mesh->vertexBuffer->Allocate();
		mesh->indexBuffer->Allocate();
		modelGameObject->getTransform()->position = { 0.0f, -2.0f, 0.0f };
		modelGameObject->getTransform()->rotation = glm::quat(glm::radians(glm::vec3(10.0f, 225.0f, -10.0f)));
		modelGameObject->getTransform()->scale = { 1.0f, 1.0f, 1.0f };
		modelGameObject->addComponent(meshRenderer);
		meshRenderer->setMesh(mesh);

		// Create Model
		auto model1 = IO::loadObj("resources/models/torus.obj");
		auto modelGameObject1 = new GameObject();
		auto meshRenderer1 = new Components::MeshRenderer();
		auto mesh1 = model1->meshes[0];

		mesh1->vertexBuffer->Allocate();
		mesh1->indexBuffer->Allocate();
		modelGameObject1->getTransform()->position = { 2.0f, -2.0f, 0.0f };
		modelGameObject1->getTransform()->rotation = glm::quat(glm::radians(glm::vec3(10.0f, 225.0f, -10.0f)));
		modelGameObject1->getTransform()->scale = { 0.5f, 0.5f, 0.5f };
		modelGameObject1->addComponent(meshRenderer1);
		meshRenderer1->setMesh(mesh1);

		auto modelGameObject2 = new GameObject();
		auto meshRenderer2 = new Components::MeshRenderer();
		auto mesh2 = mesh;
		
		modelGameObject2->getTransform()->position = { -2.0f, -1.0f, 0.0f };
		modelGameObject2->getTransform()->rotation = glm::quat(glm::radians(glm::vec3(10.0f, 225.0f, -10.0f)));
		modelGameObject2->getTransform()->scale = { 0.75f, 0.75f, 0.75f };
		modelGameObject2->addComponent(meshRenderer2);
		meshRenderer2->setMesh(mesh2);

		// Add GameObjects
		AddGameObject(cameraGameObject);
		AddGameObject(modelGameObject);
		AddGameObject(modelGameObject1);
		AddGameObject(modelGameObject2);
	}

	Scene::~Scene()
	{
		for (const auto& gameObject : gameObjects)
		{
			delete gameObject;
		}
	}


	void Scene::OnUpdate()
	{
		for (const auto& gameObject : gameObjects)
		{
			gameObject->OnUpdate();
		}

		auto transform = gameObjects[1]->getTransform();
		auto position = transform->position;
		auto deltaPosition = glm::vec3 { 0.0f };
		auto scale = transform->scale;

		if (InputAPI::GetKey(KeyCode::KEY_W))
		{
			deltaPosition.y += 1.0f;
		}

		if (InputAPI::GetKey(KeyCode::KEY_S))
		{
			deltaPosition.y -= 1.0f;
		}

		if (InputAPI::GetKey(KeyCode::KEY_D))
		{
			deltaPosition.x += 1.0f;
		}

		if (InputAPI::GetKey(KeyCode::KEY_A))
		{
			deltaPosition.x -= 1.0f;
		}

		if (InputAPI::GetKeyDown(KeyCode::KEY_UP))
		{
			scale = scale * -1.0f;
		}

		if (InputAPI::GetKeyUp(KeyCode::KEY_UP))
		{
			scale = scale * -1.0f;
		}

		transform->position = position + deltaPosition * (float) TimeAPI::DeltaTime() * 2.0f;
		transform->scale = scale;

		gameObjects[2]->getTransform()->position = { (InputAPI::GetMouseX() - 300) * 0.01f, (InputAPI::GetMouseY() - 300) * 0.01f, 0.0f };
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