#include "game_object.h"
#include "transform.h"


namespace Engine
{
	GameObject::GameObject()
	{
		transform = new Components::Transform();
		addComponent(transform);
	}

	GameObject::~GameObject()
	{
		delete transform;

		for (const auto& component : components)
		{
			delete component;
		}
	}


	void GameObject::OnUpdate()
	{
		for (const auto& component : components)
		{
			component->OnUpdate();
		}
	}

	void GameObject::OnRender()
	{
		for (const auto& component : components)
		{
			component->OnRender();
		}
	}

	Components::Transform* GameObject::getTransform()
	{
		return transform;
	}
}