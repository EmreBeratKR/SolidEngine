#include "component.h"
#include "../game_object.h"


namespace Engine::Components
{
	GameObject* Component::getGameObject()
	{
		return gameObject;
	}

	void Component::setGameObject(GameObject* gameObject)
	{
		this->gameObject = gameObject;
	}

	Transform* Component::getTransform()
	{
		return gameObject->getTransform();
	}
}