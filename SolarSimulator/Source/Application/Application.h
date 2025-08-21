#pragma once
#include <iostream>
#include "Core.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "LogSys/Log.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "../Mesh/Model.h"
#include "Camera/Camera.h"
#include "Entity/SkyBox.h"

#include "../3rdParty/glm/mat4x4.hpp"
#include "../3rdParty/glm/glm.hpp"
#include "../3rdParty/glm/gtc/type_ptr.hpp"


#include "UI/UI.h"

namespace Simulator
{
	//Main Class
	class Application
	{
	public:
		 Application(const int pWidth, const int pHeight, const char* pTitle);
		~Application();

		void Run();

		void Setup();
		void Input();
		void Update();
		void UpdateUI();
		void Render();

	private:
		WINDOW m_Window = NULL;
		UI* m_UI = NULL;
		Log m_Log;


		Camera m_Camera;

		Shader m_Shader;
		Shader m_SunShader;

		Model m_Sun;
		Model m_Mercury;
		Model m_Venus;
		Model m_Earth;
		Model m_Mars;
		Model m_Jupiter;
		Model m_Saturn;
		Model m_SaturnRing;
		Model m_Uranus;
		Model m_Neptone;

		SkyBox m_Skybox;

		glm::vec3 m_SunPos = glm::vec3(0.0f, 0.0f, 0.0f);
		glm::vec3 m_EarthPos = glm::vec3(10.0f, -10.f, 10.0f);
	};
};