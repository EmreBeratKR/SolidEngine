#include "camera.h"
#include "src/core/engine_window.h"
#include "transform.h";

namespace Engine::Components
{
	Camera::Camera()
	{
		
	}

	Camera::~Camera()
	{

	}


	Camera* Camera::main{nullptr};


	glm::mat4 Camera::getProjectionMatrix()
	{
		auto aspectRatio = EngineWindow::main->getAspectRatio();

		if (fabs(aspectRatio - this->aspectRatio) > FLT_EPSILON)
		{
			this->aspectRatio = aspectRatio;
			updateProjectionMatrix();
		}

		return projectionMatrix;
	}

	glm::mat4 Camera::getViewMatrix()
	{
		auto transform = getTransform();
		auto matrix = transform->getMatrix();

		return glm::inverse(matrix);
	}

	void Camera::updateProjectionMatrix()
	{
		projectionMatrix = createPerspectiveProjectionMatrix(fov, aspectRatio, nearClip, farClip);
	}


	Camera* Camera::perspective(float fov, float nearClip, float farClip)
	{
		auto camera = new Camera();
		auto aspectRatio = EngineWindow::main->getAspectRatio();

		camera->fov = fov;
		camera->aspectRatio = aspectRatio;
		camera->nearClip = nearClip;
		camera->farClip = farClip;
		camera->updateProjectionMatrix();

		return camera;
	}

	glm::mat4 Camera::createPerspectiveProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip)
	{
		auto matrix = glm::perspectiveLH_ZO(glm::radians(fov), aspectRatio, nearClip, farClip);

		matrix[1][1] *= -1;

		return matrix;
	}
}