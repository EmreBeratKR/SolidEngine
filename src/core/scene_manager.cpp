#include "scene_manager.h"
#include "scene.h";


namespace Engine
{
	Scene* SceneManager::activeScene{nullptr};


	void SceneManager::OnUpdate()
	{
		activeScene->OnUpdate();
	}

	void SceneManager::OnRender()
	{
		activeScene->OnRender();
	}
}