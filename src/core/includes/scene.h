#pragma once


#include <vector>


#include "fwd.h"


namespace Engine
{
	class Scene
	{
	public:
		Scene();
		~Scene();
	public:
		void OnUpdate();
		void OnRender();
		void AddGameObject(GameObject* gameObect);
	private:
		std::vector<GameObject*> gameObjects;
	};
}