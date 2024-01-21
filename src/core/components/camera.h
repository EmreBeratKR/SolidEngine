#pragma once

#include "glm/glm.hpp"
#include "component.h"

namespace Engine::Components
{
	class Camera : public Component
	{
	public:
		~Camera();
	private:
		Camera();
	public:
		glm::mat4 getProjectionMatrix();
		glm::mat4 getViewMatrix();
	private:
		void updateProjectionMatrix();

	public:
		static Camera* perspective(float fov, float nearClip, float farClip);

	private:
		static glm::mat4 createPerspectiveProjectionMatrix(float fov, float aspectRatio, float nearClip, float farClip);

	public:
		static Camera* main;

	private:
		glm::mat4 projectionMatrix{1.0f};
		float aspectRatio;
		float fov;
		float nearClip;
		float farClip;
	};
}