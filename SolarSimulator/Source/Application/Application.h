#pragma once
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
#include <future>

#include "Core.h"
#include "Renderer/Renderer.h"
#include "Window/Window.h"
#include "LogSys/Log.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Camera/Camera.h"
#include "Entity/SkyBox.h"
#include "Entity/Grid.h"
#include "Timer/Timer.h"
#include  "Renderer/ShaderManager.h"
#include "Physics/Physics.h"
#include "Renderer/FrameBuffer.h"

#include "Entity/Celestial/Sun.h"
#include "Entity/Celestial/Mercury.h"
#include "Entity/Celestial/Venus.h"
#include "Entity/Celestial/Earth.h"
#include "Entity/Celestial/Mars.h"
#include "Entity/Celestial/Jupiter.h"
#include "Entity/Celestial/Saturn.h"
#include "Entity/Celestial/Uranus.h"
#include "Entity/Celestial/Neptone.h"

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


	private:
		void Setup();
		void Input();
		void Update();
		void UpdateUI();
		void Render();

		bool Bloom();

	private:
		WINDOW m_Window = NULL;
		UI* m_UI = NULL;
		Log m_Log;


		
		FrameBuffer m_Bloom[2];
		FrameBuffer m_SceneBuffer;
		FrameBuffer m_BlurFbo;

		Mesh m_RenderingQuad;

		uint32 m_BloomShader;
		uint32 m_ScreenShader;
		uint32 m_BlurShader;

		Camera m_Camera;
		SkyBox m_Skybox;
		bool m_LockedFPS = false;
		bool m_BloomEffect=true;

	};
};