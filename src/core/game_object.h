#pragma once

#include "vector"

#include "components/transform.fwd.h"
#include "components/component.h"
#include "object.h"


namespace Engine
{
	class GameObject : public Object
	{
	public:
		GameObject();
		~GameObject();
	public:
		Components::Transform* getTransform();
		template<typename T> void addComponent(T* component);
	private:
		Components::Transform* transform;
		std::vector<Components::Component> components;
	};
}