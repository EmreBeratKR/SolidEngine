#pragma once

#include "components/transform.fwd.h"

namespace Engine
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();
	public:
		Components::Transform* getTransform();
	private:
		Components::Transform* transform;
	};
}