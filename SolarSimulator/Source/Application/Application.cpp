#include "Application.h"

namespace Simulator
{
	Application::Application(const int pWidth, const int pHeight, const char * pTitle)
		: m_Camera(0.1f, 800.0f, 45.0f, 2.0f)
	{
		m_Log.SetLoggingLevel(LOG_LV2);
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

		m_Camera.SetPosition(35.0f, 70.0f, 94.0f);
		m_Camera.SetPitch(-38.0f);
		m_Camera.SetYaw(272.0f);

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
		m_ScreenShader = ShaderManager::Self()->CreateNewShaderFromPath(Path + "Shaders/Screen.glsl");

		m_BlurShader = ShaderManager::Self()->CreateNewShaderFromPath(Path + "Shaders/Blur.glsl");
		m_BloomShader = ShaderManager::Self()->CreateNewShaderFromPath(Path + "Shaders/Bloom.glsl");

		Log::GetSelf()->SetInfo("Shader Loading Took: %f ms", timer1.GetTime());

		//Add Shaders to UI:

		for (int i = 0 ; i < ShaderManager::Self()->GetShaderNums() ; i++)
		{
			m_UI->CreateButton("Shaders", "Reload " + (*ShaderManager::Self())[i].GetShaderName(), ImVec2(10.0f, 30.0f + (i*30.0f)));
		}


		Timer timer2;
		Renderer::Get()->NewEntity(new Grid(S_Grid, 50, 50, glm::vec3(-250, 0.0f, -250.0f), 10.0f));
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

		//Setting FrameBuffer:
		m_SceneBuffer.CreateFrameBuffer(m_Window->GetWidth(), m_Window->GetHeigt(), 1);
		m_BlurFbo.CreateFrameBuffer(m_Window->GetWidth(), m_Window->GetHeigt(), 2);

		m_Bloom[0].CreateFrameBuffer(m_Window->GetWidth(), m_Window->GetHeigt());
		m_Bloom[1].CreateFrameBuffer(m_Window->GetWidth(), m_Window->GetHeigt());


		std::vector<Vertex> Quad =
		{
			{glm::vec3(-1.0f,  1.0f,0.0f),glm::vec3(0.0f),glm::vec2(0.0f, 1.0f)},
			{glm::vec3(-1.0f, -1.0f,0.0f),glm::vec3(0.0f),glm::vec2(0.0f, 0.0f)},
			{glm::vec3(1.0f, -1.0f,0.0f),glm::vec3(0.0f),glm::vec2(1.0f, 0.0f)},
			{glm::vec3(-1.0f,  1.0f,0.0f),glm::vec3(0.0f),glm::vec2(0.0f, 1.0f)},
			{glm::vec3(1.0f, -1.0f,0.0f),glm::vec3(0.0f),glm::vec2(1.0f, 0.0f)},
			{glm::vec3(1.0f,  1.0f,0.0f),glm::vec3(0.0f),glm::vec2(1.0f, 1.0f)}
		};

		m_RenderingQuad.SetUp(Quad, std::vector<uint16>());
		ShaderManager::Self()->GetShader(m_ScreenShader).SetUniformInt1("screenTexture", 0);
		ShaderManager::Self()->GetShader(m_ScreenShader).SetUniformInt1("BloomEffect", 1);

		ShaderManager::Self()->GetShader(m_BloomShader).SetUniformInt1("Texture", 0);




		m_UI->GetSliderF("Setter", "Gamma")->GetValue() = 1.0f;
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


		ShaderManager::Self()->GetShader(m_ScreenShader).SetUniformFloat1("Gamma", m_UI->GetSliderF("Setter", "Gamma")->GetValue());

		Physics::Get()->Update();
	
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


		if (m_UI->GetWindow("Camera").ShouldRender())
		{
			m_UI->GetText("Camera", "CameraPosX")->GetText() = "Camera X:" + std::to_string(m_Camera.GetPosition().x);
			m_UI->GetText("Camera", "CameraPosY")->GetText() = "Camera Y:" + std::to_string(m_Camera.GetPosition().y);
			m_UI->GetText("Camera", "CameraPosZ")->GetText() = "Camera Z:" + std::to_string(m_Camera.GetPosition().z);
			m_UI->GetText("Camera", "CameraYaw")->GetText() = "Camera Yaw:" + std::to_string(m_Camera.GetYaw());
			m_UI->GetText("Camera", "CameraPitch")->GetText() = "Camera Pitch:" + std::to_string(m_Camera.GetPitch());
		}


		m_LockedFPS = m_UI->GetCheckbox("Config", "Lock FPS to 60")->GetState();
		
	
		if (m_UI->GetWindow("Setter").ShouldRender())
		{
			m_BloomEffect = m_UI->GetCheckbox("Setter", "Bloom")->GetState();
			ShaderManager::Self()->GetShader(m_ScreenShader).SetUniformInt1("UseBloom", m_BloomEffect);
		}

	}

	void Application::Render()
	{

		//Render the scene to our framebuffer:
		m_SceneBuffer.Bind();
		m_SceneBuffer.ClearBuffer();
		glEnable(GL_DEPTH_TEST);
		Renderer::Get()->Draw();
		m_Skybox.RenderSkyBox();


		// Render the scene to Bloom FrameBuffer
		m_BlurFbo.Bind();
		m_BlurFbo.ClearBuffer();
		glDisable(GL_DEPTH_TEST);
		m_SceneBuffer.BindColorBuffer(0);
		m_RenderingQuad.Render(ShaderManager::Self()->GetShader(m_BloomShader));

		//Blur the Bright spots:
		bool Final=0;
		if (m_BloomEffect)
			Final = Bloom();

		//Render the FrameBuffer Texture to screen:
		m_BlurFbo.Unbind();
		Renderer::Get()->ClearDefFrameBuffer();
		glDisable(GL_DEPTH_TEST);
		m_BlurFbo.BindColorBuffer(0, 0);
		m_Bloom[Final].BindColorBuffer(0, 1);
		m_RenderingQuad.Render(ShaderManager::Self()->GetShader(m_ScreenShader));


		m_UI->Render(); //Rendering UI Eelemts.
		m_Window->WindowUpdate();
	}

	bool Application::Bloom()
	{
		bool Horizontal = true, First = true;

		uint32 Amount = 10;
		for (int i = 0; i < 10; i++)
		{
			m_Bloom[Horizontal].Bind();
			ShaderManager::Self()->GetShader(m_BlurShader).SetUniformInt1("horizontal", Horizontal);

			if (First)
			{
				m_BlurFbo.BindColorBuffer(1, 0);
			}
			else
			{
				m_Bloom[!Horizontal].BindColorBuffer(0);
			}
			m_RenderingQuad.Render(ShaderManager::Self()->GetShader(m_BlurShader));
			Horizontal = !Horizontal;
			First = false;
		}
		return !Horizontal;
	}

};