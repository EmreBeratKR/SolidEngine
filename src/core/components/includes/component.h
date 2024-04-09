#pragma once


#include "object.h"
#include "fwd.h"


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