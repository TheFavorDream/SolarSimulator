#include "Application.h"



namespace Simulator
{
	Application::Application(const int pWidth, const int pHeight, const char * pTitle)
		: m_Camera(0.1f, 800.0f, 45.0f, 2.0f)
	{
		m_Log.SetInfo("Application Started");
		m_Window = Window::CreateWindowObject(pWidth, pHeight, pTitle);
		m_UI = UI::CreateUIInstance();

		Renderer::Get(); // To Allocate memory
		Setup();
	}
	Application::~Application()
	{
		delete m_UI;
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Window->ShouldWindowClose())
		{
			Input();
			Update();
			UpdateUI();
			Render();
		}
	}



	//Runs once in the start
	void Application::Setup()
	{

		m_Camera.SetPosition(25.0f, 52.0f, -17.0f);
		m_Camera.SetPitch(-41.0f);
		m_Camera.SetYaw(-274.0f);

		m_Shader.CreateShader("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Shaders\\basic.glsl");
		m_SunShader.CreateShader("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Shaders\\Sun.glsl");

		m_UI->LoadUI("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\UI\\UI.json");

		m_Sun.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Sun.gltf");
		m_Mercury.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Mercury.gltf");
		m_Venus.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Venus.gltf");
		m_Earth.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Earth.gltf");
		m_Mars.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Mars.gltf");
		m_Jupiter.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Jupiter.gltf");
		m_Saturn.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Saturn.gltf");
		m_SaturnRing.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\SaturnRing.gltf");
		m_Uranus.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Uranus.gltf");
		m_Neptone.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Neptone.gltf");

		//m_Skybox.CreateSkyBox("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Assets\\test.jpg");

		m_Shader.SetUniformFloat1("AmbientStrength", 0.1f);
		m_Shader.SetUniformFloat3("SunPosition", m_SunPos.x, m_SunPos.y, m_SunPos.z);
		m_Shader.SetUniformFloat3("LightColor", 1.0f, 1.0f, 1.0f);



	}


	void Application::Input()
	{
		static uint32 LastTime = 0;
		uint32 Current = glfwGetTime();
		if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_R) == GLFW_PRESS && Current - LastTime >= 1)
		{
			m_UI->LoadUI("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\UI\\UI.json");
			LastTime = Current;
		}

		m_UI->SetWindowRenderState("Setter",m_UI->GetCheckbox("Config", "Show Setter Menu")->GetState());


		m_Camera.HandleCameraMovement();
		m_Camera.HandleMouseMovement();
		m_UI->Event();//UI Events
		glfwPollEvents();


	}

	void Application::Update()
	{
		Input3F* ColorRef = m_UI->GetInput3F("Setter", "BG Color");
		Renderer::Get()->SetClearColor(ColorRef->GetValue1(), ColorRef->GetValue2(),ColorRef->GetValue3());



		float Time = (float)glfwGetTime();

		m_Mercury.GetModelMatrix() = glm::mat4(1.0f);
		m_Mercury.GetModelMatrix() = glm::translate(m_Mercury.GetModelMatrix(), glm::vec3(sin(Time*0.01f)*20.0f, 0.0f, cos(Time*0.01f)*20.0f));
		m_Mercury.GetModelMatrix() = glm::rotate(m_Mercury.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));

		m_Venus.GetModelMatrix() = glm::mat4(1.0f);
		m_Venus.GetModelMatrix() = glm::translate(m_Venus.GetModelMatrix(), glm::vec3(sin(Time*0.02f)*30.0f, 0.0f, cos(Time*0.02f)*30.0f));
		m_Venus.GetModelMatrix() = glm::rotate(m_Venus.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));

		m_Earth.GetModelMatrix() = glm::mat4(1.0f);
		m_EarthPos = glm::vec3(sin(Time*0.03f)*40.0f, 0.0f, cos(Time*0.03f)*40.0f);
		m_Earth.GetModelMatrix() = glm::translate(m_Earth.GetModelMatrix(), m_EarthPos);
		m_Earth.GetModelMatrix() = glm::rotate(m_Earth.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));
	
		m_Mars.GetModelMatrix() = glm::mat4(1.0f);
		m_Mars.GetModelMatrix() = glm::translate(m_Mars.GetModelMatrix(), glm::vec3(sin(Time*0.04f)*50.0f, 0.0f, cos(Time*0.04f)*50.0f));
		m_Mars.GetModelMatrix() = glm::rotate(m_Mars.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));

		m_Jupiter.GetModelMatrix() = glm::mat4(1.0f);
		m_Jupiter.GetModelMatrix() = glm::translate(m_Jupiter.GetModelMatrix(), glm::vec3(sin(Time*0.05f)*60.0f, 0.0f, cos(Time*0.05f)*60.0f));
		m_Jupiter.GetModelMatrix() = glm::rotate(m_Jupiter.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));

		m_Saturn.GetModelMatrix() = glm::mat4(1.0f);
		m_Saturn.GetModelMatrix() = glm::translate(m_Saturn.GetModelMatrix(), glm::vec3(sin(Time*0.06f)*70.0f, 0.0f, cos(Time*0.06f)*70.0f));
		m_Saturn.GetModelMatrix() = glm::rotate(m_Saturn.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));

		m_SaturnRing.GetModelMatrix() = glm::mat4(1.0f);
		m_SaturnRing.GetModelMatrix() = glm::translate(m_SaturnRing.GetModelMatrix(), glm::vec3(sin(Time*0.06f)*70.0f, 0.0f, cos(Time*0.06f)*70.0f));
		m_SaturnRing.GetModelMatrix() = glm::scale(m_SaturnRing.GetModelMatrix(), glm::vec3(3.0f, 0.01f, 3.0f));
		m_SaturnRing.GetModelMatrix() = glm::rotate(m_SaturnRing.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));

		m_Uranus.GetModelMatrix() = glm::mat4(1.0f);
		m_Uranus.GetModelMatrix() = glm::translate(m_Uranus.GetModelMatrix(), glm::vec3(sin(Time*0.07f)*80.0f, 0.0f, cos(Time*0.07f)*80.0f));
		m_Uranus.GetModelMatrix() = glm::rotate(m_Uranus.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));

		m_Neptone.GetModelMatrix() = glm::mat4(1.0f);
		m_Neptone.GetModelMatrix() = glm::translate(m_Neptone.GetModelMatrix(), glm::vec3(sin(Time*0.08f)*90.0f, 0.0f, cos(Time*0.08f)*90.0f));
		m_Neptone.GetModelMatrix() = glm::rotate(m_Neptone.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));

		m_Sun.GetModelMatrix() = glm::mat4(1.0f);
		m_Sun.GetModelMatrix() = glm::translate(m_Sun.GetModelMatrix(), m_SunPos);
		m_Sun.GetModelMatrix() = glm::scale(m_Sun.GetModelMatrix(), glm::vec3(10.0f, 10.0f, 10.0f));
	}

	void Application::UpdateUI()
	{
		m_UI->GetText("Config", "CameraPosX")->GetText() = "Camera X:" + std::to_string(m_Camera.GetPosition().x);
		m_UI->GetText("Config", "CameraPosY")->GetText() = "Camera Y:" + std::to_string(m_Camera.GetPosition().y);
		m_UI->GetText("Config", "CameraPosZ")->GetText() = "Camera Z:" + std::to_string(m_Camera.GetPosition().z);

		m_UI->GetText("Config", "CameraYaw")->GetText() = "Camera Yaw:" + std::to_string(m_Camera.GetYaw());
		m_UI->GetText("Config", "CameraPitch")->GetText() = "Camera Pitch:" + std::to_string(m_Camera.GetPitch());
	}

	void Application::Render()
	{
		Renderer::Get()->Draw();

		m_Sun.Render(m_SunShader, m_Camera);
		m_Mercury.Render(m_Shader, m_Camera);
		m_Venus.Render(m_Shader, m_Camera);
		m_Earth.Render(m_Shader, m_Camera);
		m_Mars.Render(m_Shader, m_Camera);
		m_Jupiter.Render(m_Shader, m_Camera);
		m_Saturn.Render(m_Shader, m_Camera);
		m_SaturnRing.Render(m_SunShader, m_Camera);
		m_Uranus.Render(m_Shader, m_Camera);
		m_Neptone.Render(m_Shader, m_Camera);
		//m_Skybox.RenderSkyBox(m_Camera);


		m_UI->Render(); //Rendering UI Eelemts.
		m_Window->WindowUpdate();
	}
};