#pragma once
#include <iostream>
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "LogSys/Log.h"
#include "Mesh/VertexBuffer.h"

namespace Simulator
{
	//Main Class
	class Application
	{
	public:
		 Application(const int pWidth, const int pHeight, const char* pTitle);
		~Application();

		void Run();

	private:
		WINDOW m_Window = NULL;
		Log m_Log;
		VertexBuffer m_VBO;
	};
};