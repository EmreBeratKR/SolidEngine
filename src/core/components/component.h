#pragma once

#include "src/core/game_object.fwd.h"
#include "transform.fwd.h"
#include "src/core/object.h"

namespace Engine::Components
{
	class Component : public Object
	{
	public:
		virtual void OnUpdate() {};
		virtual void OnRender() {};
		GameObject* getGameObject();
		void setGameObject(GameObject* gameObject);
		Transform* getTransform();
	private:
		GameObject* gameObject;
	};
}