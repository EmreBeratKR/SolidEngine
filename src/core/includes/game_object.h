#pragma once

#include <vector>


#include "object.h"
#include "fwd.h"


namespace Engine
{
	class GameObject : public Object
	{
	public:
		GameObject();
		~GameObject();
	public:
		void OnUpdate();
		void OnRender();
		Components::Transform* getTransform();
	public:
		template<typename T> void addComponent(T* component)
		{
			component->setGameObject(this);
			components.push_back(component);
		}
	private:
		Components::Transform* transform;
		std::vector<Components::Component*> components;
	};
}