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
		void Render();

	private:
		WINDOW m_Window = NULL;
		UI* m_UI = NULL;
		Log m_Log;


		Shader m_Test;
		Camera m_Camera;

		Model m_Earth;
		Model m_Moon;

	};
};