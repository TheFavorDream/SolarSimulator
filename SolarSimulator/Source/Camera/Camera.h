#pragma once
#include "Core.h"
#include "../UI/UI.h"
#include "../LogSys/Log.h"
#include "../Window/Window.h"
#include "../../3rdParty/glfw/include/GLFW/glfw3.h"
#include "../../3rdParty/glew/include/GL/glew.h"
#include "../../3rdParty/glm/glm.hpp"
#include "../../3rdParty/glm/matrix.hpp"
#include "../../3rdParty/glm/gtc/matrix_transform.hpp"


namespace Simulator
{
	class Camera
	{
	public:
		  Camera(float pNPlane, float pFPlane, float pPov, float pAspect, glm::vec3 pPostion = glm::vec3(0.0f, 0.0f, 3.0f));
		 ~Camera();


		 void HandleCameraMovement();
		 void HandleMouseMovement();

		glm::mat4& GetView();
		glm::mat4& GetProjection();

		void SetPosition(float pX, float pY, float pZ);
		void SetYaw(float pYaw);
		void SetPitch(float pPitch);

		inline const glm::vec3& GetPosition() { return m_Position; }
		inline float GetYaw() { return m_Yaw; }
		inline float GetPitch() { return m_Pitch; }

	private:

		void UpdateCameraDirection();

	private:
		glm::vec3 m_Position;
		glm::vec3 m_Front;
		glm::vec3 m_Up;

		float m_Yaw   = 268.0f;
		float m_Pitch = -5.0f;
		float m_Speed = 0.0f;
	
		float m_NearPlane = 0.0f;
		float m_FarPlane  = 0.0f;
		float m_Pov = 0.0f;
		float m_AspectRatio = 0.0f;

		bool m_IsFirstClick = true;
		float m_Sensetivity = 0.25f;
		double m_LastX, m_LastY;

		glm::mat4 m_Projection;
		glm::mat4 m_View;
	};
};
