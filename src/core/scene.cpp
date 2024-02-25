#include <iostream>


#include "scene.h"
#include "src/core/game_object.h"
#include "src/core/components/transform.h"
#include "src/core/components/camera.h"


namespace Engine
{
	Scene::Scene()
	{
		auto go = new GameObject();
		auto transform = go->getTransform();
		auto camera = Components::Camera::perspective(60.0f, 0.01f, 100.0f);

		go->addComponent(camera);
		transform->position = { 0.0f, 0.0f, -8.0f };

		Components::Camera::main = camera;
	}

	Scene::~Scene()
	{

	}
}