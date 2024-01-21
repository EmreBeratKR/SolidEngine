#pragma once

#include "glm/glm.hpp"

namespace Engine::Components
{
	class Camera
	{
	public:
		~Camera();
	private:
		Camera();
	public:
		glm::mat4 getProjectionMatrix();

	public:
		static Camera* perspective(float fov, float nearClip, float farClip);

	public:
		static Camera* main;

	private:
		float fov;
		float nearClip;
		float farClip;
	};
}