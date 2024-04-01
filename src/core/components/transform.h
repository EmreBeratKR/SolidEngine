#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>


#include "component.h"


namespace Engine::Components
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();
	public:
		glm::mat4 getMatrix();
	public:
		glm::vec3 position{0.0f};
		glm::quat rotation{1.0f, 0.0f, 0.0f, 0.0f};
		glm::vec3 scale{1.0f};
	};
}