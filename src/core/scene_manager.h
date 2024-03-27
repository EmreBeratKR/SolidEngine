#pragma once


#include "layer.h"


namespace Engine
{
	class Scene;

	class SceneManager : public Layer
	{
	public:
		virtual void OnUpdate();
		virtual void OnRender();
	public:
		static Scene* activeScene;
	};
}