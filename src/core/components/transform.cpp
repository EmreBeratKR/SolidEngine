#include "transform.h"


namespace Engine::Components
{
	Transform::Transform()
	{

	}

	Transform::~Transform()
	{

	}


	glm::mat4 Transform::getMatrix()
	{
		auto translationMatrix = glm::translate(glm::mat4{ 1.0f }, position);
		auto rotationMatrix = glm::mat4_cast(rotation);

		return glm::scale(translationMatrix * rotationMatrix, scale);
	}
}