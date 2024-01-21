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
		glm::mat4 matrix{1.0f};

		matrix = glm::translate(matrix, position);
		matrix = glm::rotate(matrix, glm::eulerAngles(rotation).x, glm::vec3(1.0f, 0.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::eulerAngles(rotation).y, glm::vec3(0.0f, 1.0f, 0.0f));
		matrix = glm::rotate(matrix, glm::eulerAngles(rotation).z, glm::vec3(0.0f, 0.0f, 1.0f));
		matrix = glm::scale(matrix, scale);

		return matrix;
	}
}