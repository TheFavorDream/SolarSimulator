#include "Application.h"

namespace Simulator
{
	Application::Application(const int pWidth, const int pHeight, const char * pTitle)
		: m_Camera(0.1f, 800.0f, 45.0f, 2.0f)
	{
		m_Log.SetLoggingLevel(LOG_LV3);
		m_Log.SetInfo("Application Started");
		m_Window = Window::CreateWindowObject(pWidth, pHeight, pTitle);
		m_UI = UI::CreateUIInstance();


		Renderer::Get(); // To Allocate memory
		ShaderManager::Self();

		Setup();
	}
	Application::~Application()
	{
		delete Renderer::Get();
		delete ShaderManager::Self();
		delete m_UI;
		delete m_Window;
	}

	void Application::Run()
	{
		using namespace std::chrono_literals;
		Timer DeltaTimer;
		while (m_Window->ShouldWindowClose())
		{	


			Input();
			Update();
			UpdateUI();
			Render();


			DeltaTimer.s_DeltaTime = (m_LockedFPS)?  DeltaTimer.GetTime() : 1.0f;
			float SleepTime = ((1.0f / 120.0f)*1000.0f)-DeltaTimer.s_DeltaTime;
			SleepTime *= m_LockedFPS;
			std::this_thread::sleep_for(std::chrono::milliseconds((int)SleepTime));

		}
	}



	//Runs once in the start
	void Application::Setup()
	{

		m_Camera.SetPosition(25.0f, 52.0f, -17.0f);
		m_Camera.SetPitch(-41.0f);
		m_Camera.SetYaw(-274.0f);

		m_UI->LoadUI(std::string(PATH) + "UI/UI.json");

		//Shader Loading:

		uint32 S_Sun =   ShaderManager::Self()->CreateNewShader(std::string(PATH) + "Shaders/Sun.glsl");
		uint32 S_Earth = ShaderManager::Self()->CreateNewShader(std::string(PATH) + "Shaders/Earth.glsl");
		uint32 S_Basic = ShaderManager::Self()->CreateNewShader(std::string(PATH) + "Shaders/basic.glsl");


		Renderer::Get()->NewEntity(new Sun(std::string(PATH) + "Models/Sphere.glb", S_Sun));
		Renderer::Get()->NewEntity(new Mercury(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Venus(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Earth(std::string(PATH) + "Models/Sphere.glb", S_Earth));
		Renderer::Get()->NewEntity(new Mars(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Jupiter(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Saturn(std::string(PATH) + "Models/Sphere.glb", std::string(PATH) + "Models/Ring.glb", S_Basic));
		Renderer::Get()->NewEntity(new Uranus(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Neptone(std::string(PATH) + "Models/Sphere.glb",S_Basic));

		
		std::vector<std::string> Paths = { "right.png", "left.png", "bottom.png", "top.png", "front.png", "back.png" };
		m_Skybox.CreateSkyBox(std::string(PATH) + "Assets/Skybox/", Paths);

	}


	void Application::Input()
	{
		m_UI->SetWindowRenderState("Setter",m_UI->GetCheckbox("Config", "Show Setter Menu")->GetState());


		m_Camera.HandleCameraMovement();
		m_Camera.HandleMouseMovement();
		m_UI->Event();//UI Events
		glfwPollEvents();


	}

	void Application::Update()
	{

		ShaderManager::Self()->BroadCastUniformMat4("View", m_Camera.GetView());
		ShaderManager::Self()->BroadCastUniformMat4("Projection", m_Camera.GetProjection());

		ShaderManager::Self()->BroadCastUniform1F("light.Ambient", 0.2f);


		(*Renderer::Get())[SUN]->GetPosition() = m_UI->GetInput3F("Setter", "Sun Position")->GetValue();
		ShaderManager::Self()->BroadCastUniform3F("light.LightPosition", m_UI->GetInput3F("Setter", "Sun Position")->GetValue());
		ShaderManager::Self()->BroadCastUniform3F("light.LightColor", m_UI->GetInput3F("Setter", "Emition Color")->GetValue());
		ShaderManager::Self()->BroadCastUniform3F("ViewPos", m_Camera.GetPosition().x, m_Camera.GetPosition().y, m_Camera.GetPosition().z);

		ShaderManager::Self()->BroadCastUniform1F("light.Constant", m_UI->GetInputF("Setter", "Constant")->GetValue());
		ShaderManager::Self()->BroadCastUniform1F("light.Linear", m_UI->GetInputF("Setter", "Linear")->GetValue());
		ShaderManager::Self()->BroadCastUniform1F("light.Quadratic", m_UI->GetInputF("Setter", "Quad")->GetValue());


	
	}

	void Application::UpdateUI()
	{
		m_UI->GetText("Config", "CameraPosX")->GetText() = "Camera X:" + std::to_string(m_Camera.GetPosition().x);
		m_UI->GetText("Config", "CameraPosY")->GetText() = "Camera Y:" + std::to_string(m_Camera.GetPosition().y);
		m_UI->GetText("Config", "CameraPosZ")->GetText() = "Camera Z:" + std::to_string(m_Camera.GetPosition().z);

		m_UI->GetText("Config", "CameraYaw")->GetText() = "Camera Yaw:" + std::to_string(m_Camera.GetYaw());
		m_UI->GetText("Config", "CameraPitch")->GetText() = "Camera Pitch:" + std::to_string(m_Camera.GetPitch());

		m_UI->GetText("Config", "DeltaTime")->GetText() = "DeltaTime(ms)" + std::to_string(Timer::s_DeltaTime);

		m_LockedFPS = m_UI->GetCheckbox("Config", "Lock FPS to 60")->GetState();
		
	

	}

	void Application::Render()
	{

		Renderer::Get()->Draw();

		m_Skybox.RenderSkyBox();

		m_UI->Render(); //Rendering UI Eelemts.
		m_Window->WindowUpdate();
	}
};