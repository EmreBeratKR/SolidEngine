#include "game_object.h"
#include "src/core/components/transform.h"


namespace Engine
{
	GameObject::GameObject()
	{
		transform = new Components::Transform();
		addComponent(transform);
	}

	GameObject::~GameObject()
	{

	}


	Components::Transform* GameObject::getTransform()
	{
		return transform;
	}

	template<typename T>
	void GameObject::addComponent(T* component)
	{
		component->setGameObject(this);
		//components.push_back(component);
	}
}