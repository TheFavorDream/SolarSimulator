#pragma once
#include <iostream>
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "LogSys/Log.h"
#include "Renderer/Shader.h"
#include "Mesh/Mesh.h"
#include "../3rdParty/glm/mat4x4.hpp"
#include "../3rdParty/glm/glm.hpp"
#include "../3rdParty/glm/gtc/type_ptr.hpp"

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
		Log m_Log;

		Shader m_Test;
		Mesh Triangle;

		std::vector<Vertex> Vertices =
		{
			{glm::vec3(-0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
			{glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
			{glm::vec3( 0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f)},
			{glm::vec3( 0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f)},

		};
		std::vector<uint32> Indices = {0, 1, 2, 1, 2, 3};
		glm::mat4 Model = glm::mat4(1.0f);
	};
};