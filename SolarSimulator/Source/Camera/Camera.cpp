#include "Camera.h"

namespace Simulator
{
	Camera::Camera(float pNPlane, float pFPlane, float pPov, float pAspect, glm::vec3 pPostion)
	{
		this->m_FarPlane = pFPlane;
		this->m_NearPlane = pNPlane;
		this->m_Pov = pPov;
		this->m_AspectRatio = pAspect;
		this->m_Position = pPostion;
		this->m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		this->m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->m_Speed = 0.12f;
		this->m_View = glm::mat4(1.0f);
		this->m_Projection = glm::mat4(1.0f);
		Log::GetSelf()->SetInfo("Camera Setted up");
	}

	Camera::~Camera()
	{
	}

	void Camera::HandleCameraMovement()
	{

		if (m_CinamaticMovement)
		{

			float Height = UI::Self()->GetInputF("Camera", "Height")->GetValue();
			m_OrbitRadius = UI::Self()->GetInputF("Camera", "Radius")->GetValue();

			float Time = glfwGetTime()*UI::Self()->GetInputF("Camera", "Speed")->GetValue();
			m_Position = glm::vec3(sin(Time)*m_OrbitRadius, Height, cos(Time)*m_OrbitRadius);

			m_Front.x = -sin(Time);
			m_Front.z = -cos(Time);

			return;
		}

		if (UI::Self()->IsUsingKeyBoard())
			return;


		if (glfwGetKey(Window::GetWindowInstance()->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			m_Position += m_Front * m_Speed * Timer::s_DeltaTime;
		}
		else if (glfwGetKey(Window::GetWindowInstance()->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			m_Position += -m_Front * m_Speed * Timer::s_DeltaTime;
		}

		else if (glfwGetKey(Window::GetWindowInstance()->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			m_Position += -glm::normalize(glm::cross(m_Front, m_Up)) * (m_Speed * Timer::s_DeltaTime);
		}
		else if (glfwGetKey(Window::GetWindowInstance()->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			m_Position += glm::normalize(glm::cross(m_Front, m_Up)) * (m_Speed * Timer::s_DeltaTime);
		}

		else if (glfwGetKey(Window::GetWindowInstance()->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			m_Position += m_Up * (m_Speed * Timer::s_DeltaTime);
		}

		else if (glfwGetKey(Window::GetWindowInstance()->GetWindow(), GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS)
		{
			m_Position += -m_Up * m_Speed * Timer::s_DeltaTime;
		}


	}

	void Camera::HandleMouseMovement()
	{
		if (m_CinamaticMovement)
			return;
		
		if (UI::Self()->IsUsingMouse())
			return;


		if (glfwGetMouseButton(Window::GetWindowInstance()->GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		{
			float X = static_cast<float>(Window::GetWindowInstance()->GetCursorX());
			float Y = static_cast<float>(Window::GetWindowInstance()->GetCursorY());

			glfwSetInputMode(Window::GetWindowInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


			if (m_IsFirstClick)
			{
				m_LastX = X;
				m_LastY = Y;
				m_IsFirstClick = false;
				//return;
			}


			float OffsetX = (X - m_LastX)*m_Sensetivity;
			float OffsetY = (m_LastY - Y)*m_Sensetivity;

			m_LastX = X;
			m_LastY = Y;


			m_Pitch += OffsetY;
			m_Yaw += OffsetX;

			if (m_Pitch >= 90.0f)
				m_Pitch = 89.9;
			else if (m_Pitch <= -90.0f)
				m_Pitch = -89.9;

			//We make sure Yaw angle never becomes greater that 360 or smaller that -360.0f
			if (m_Yaw >= 360.0f)
			{
				m_Yaw -= 360.0f;
			}
			else if (m_Yaw <= -360.0f)
			{
				m_Yaw += 360.0f;
			}

			UpdateCameraDirection();

		}
		else
		{
			if (!m_IsFirstClick)
			{
				glfwSetInputMode(Window::GetWindowInstance()->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
				m_IsFirstClick = true;
			}
		}
	}

	glm::mat4 & Camera::GetView()
	{
		m_View = glm::lookAt(m_Position, m_Position+m_Front, m_Up);
		return m_View;
	}

	glm::mat4 & Camera::GetProjection()
	{
		m_Projection = glm::perspective(glm::radians(m_Pov), m_AspectRatio, m_NearPlane, m_FarPlane);
		return m_Projection;
	}
	void Camera::SetPosition(float pX, float pY, float pZ)
	{
		m_Position = glm::vec3(pX, pY, pZ);
	}

	void Camera::SetYaw(float pYaw)
	{
		m_Yaw = pYaw;
		glm::vec3 Dir;
		UpdateCameraDirection();
	}

	void Camera::SetPitch(float pPitch)
	{
		m_Pitch = pPitch;
		UpdateCameraDirection();

	}
	void Camera::EnableCinamaticMovement(bool pEnable)
	{
		m_CinamaticMovement = pEnable;
	}


	void Camera::UpdateCameraDirection()
	{
		glm::vec3 Dir;
		Dir.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		Dir.y = sin(glm::radians(m_Pitch));
		Dir.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(Dir);
	}
};