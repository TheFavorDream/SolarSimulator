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
		Physics::Get();

		Setup();
	}
	Application::~Application()
	{
		delete Renderer::Get();
		delete ShaderManager::Self();
		delete Physics::Get();
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

		Timer timer0;
		m_UI->LoadUI(std::string(PATH) + "UI/UI.json");
		Log::GetSelf()->SetInfo("UI Loading Took: %f ms", timer0.GetTime());

		//Shader Loading:

		Timer timer1;
		std::string Path = std::string(PATH);
		
		uint32 S_Sun = ShaderManager::Self()->CreateNewShaderFromPath(Path + "Shaders/Sun.glsl");
		uint32 S_Earth = ShaderManager::Self()->CreateNewShaderFromPath(Path + "Shaders/Earth.glsl");
		uint32 S_Basic = ShaderManager::Self()->CreateNewShaderFromPath(Path + "Shaders/basic.glsl");
		uint32 S_Grid = ShaderManager::Self()->CreateNewShaderFromPath(Path + "Shaders/Grid.glsl");
		Log::GetSelf()->SetInfo("Shader Loading Took: %f ms", timer1.GetTime());

		//Add Shaders to UI:

		for (int i = 0 ; i < ShaderManager::Self()->GetShaderNums() ; i++)
		{
			m_UI->CreateButton("Shaders", "Reload " + (*ShaderManager::Self())[i].GetShaderName(), ImVec2(10.0f, 30.0f + (i*30.0f)));
		}


		Timer timer2;
		Renderer::Get()->NewEntity(new Grid(S_Grid, 50, 50, glm::vec3(-200, 0.0f, -200.0f)));
		Renderer::Get()->NewEntity(Sun::Construct(std::string(PATH) + "Models/Sphere.glb", S_Sun));
		Renderer::Get()->NewEntity(new Mercury(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Venus(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Earth(std::string(PATH) + "Models/Sphere.glb", S_Earth));
		Renderer::Get()->NewEntity(new Mars(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Jupiter(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Saturn(std::string(PATH) + "Models/Sphere.glb", std::string(PATH) + "Models/Ring.glb", S_Basic));
		Renderer::Get()->NewEntity(new Uranus(std::string(PATH) + "Models/Sphere.glb", S_Basic));
		Renderer::Get()->NewEntity(new Neptone(std::string(PATH) + "Models/Sphere.glb",S_Basic));
		Log::GetSelf()->SetInfo("Model Loading Took: %f ms", timer2.GetTime());
		
		std::vector<std::string> Paths = { "right.png", "left.png", "bottom.png", "top.png", "front.png", "back.png" };
		m_Skybox.CreateSkyBox(std::string(PATH) + "Assets/Skybox/", Paths);

	}


	void Application::Input()
	{
		m_UI->SetWindowRenderState("Setter", m_UI->GetCheckbox("Config", "Show Setter Menu")->GetState());
		m_UI->SetWindowRenderState("Shaders", m_UI->GetCheckbox("Config", "Shaders Menu")->GetState());
		m_UI->SetWindowRenderState("Camera", m_UI->GetCheckbox("Config", "Camera Info")->GetState());


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

		Physics::Get()->Update(Renderer::Get()->GetEntities());
	
	}

	void Application::UpdateUI()
	{

		if (m_UI->GetWindow("Shaders").ShouldRender())
		{
			for (int i = 0; i < ShaderManager::Self()->GetShaderNums() - 1; i++)
			{
				if (m_UI->GetButton("Shaders", "Reload " + (*ShaderManager::Self())[i].GetShaderName())->GetState())
				{
					Log::GetSelf()->SetInfo("Shader Reloaded, %s", (*ShaderManager::Self())[i].GetShaderName());
					ShaderManager::Self()->GetShader(i).DeleteShader();
					ShaderManager::Self()->GetShader(i).CreateShader(ShaderManager::Self()->GetShader(i).GetShaderPath());

				}
			}
		}


		m_UI->GetText("Camera", "CameraPosX")->GetText() = "Camera X:" + std::to_string(m_Camera.GetPosition().x);
		m_UI->GetText("Camera", "CameraPosY")->GetText() = "Camera Y:" + std::to_string(m_Camera.GetPosition().y);
		m_UI->GetText("Camera", "CameraPosZ")->GetText() = "Camera Z:" + std::to_string(m_Camera.GetPosition().z);
		m_UI->GetText("Camera", "CameraYaw")->GetText() = "Camera Yaw:" + std::to_string(m_Camera.GetYaw());
		m_UI->GetText("Camera", "CameraPitch")->GetText() = "Camera Pitch:" + std::to_string(m_Camera.GetPitch());
		


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