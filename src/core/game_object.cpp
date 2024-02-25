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
}