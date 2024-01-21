#include "camera.h"
#include "src/core/engine_window.h"

namespace Engine::Components
{
	Camera::Camera()
	{
		fov = 0.0f;
		nearClip = 0.0f;
		farClip = 0.0f;
	}

	Camera::~Camera()
	{

	}


	Camera* Camera::main{nullptr};


	glm::mat4 Camera::getProjectionMatrix()
	{
		auto aspectRatio = EngineWindow::main->getAspectRatio();
		auto matrix = glm::perspective(glm::radians(fov), aspectRatio, nearClip, farClip);
		matrix[1][1] *= -1;
		return matrix;
	}


	Camera* Camera::perspective(float fov, float nearClip, float farClip)
	{
		auto camera = new Camera();

		camera->fov = fov;
		camera->nearClip = nearClip;
		camera->farClip = farClip;

		return camera;
	}
}