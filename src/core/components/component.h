#pragma once

#include "src/core/game_object.fwd.h"
#include "transform.fwd.h"

namespace Engine::Components
{
	class Component
	{
	public:
		GameObject* getGameObject();
		void setGameObject(GameObject* gameObject);
		Transform* getTransform();
	private:
		GameObject* gameObject;
	};
}