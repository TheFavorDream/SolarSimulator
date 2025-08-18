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
			Render();
		}
	}



	//Runs once in the start
	void Application::Setup()
	{

		m_Camera.SetPosition(0.0f, 0.0f, 10.0f);

		m_Test.CreateShader("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Shaders\\basic.glsl");
		m_UI->LoadUI("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\UI\\UI.json");

		m_Earth.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Sphere.gltf");
		m_Moon.LoadModel("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Models\\Sphere.gltf");


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

		m_Earth.GetModelMatrix() = glm::mat4(1.0f);
		m_Earth.GetModelMatrix() = glm::scale(m_Earth.GetModelMatrix(), glm::vec3(2.0f, 2.0f, 2.0f));
		m_Earth.GetModelMatrix() = glm::rotate(m_Earth.GetModelMatrix(), glm::radians(Time*50.0f), glm::vec3(0.0f, 1.0f, 0.2f));
	


		m_Moon.GetModelMatrix() = glm::mat4(1.0f);
		m_Moon.GetModelMatrix() = glm::scale(m_Moon.GetModelMatrix(), glm::vec3(0.5f, 0.5f, 0.5f));
		m_Moon.GetModelMatrix() = glm::translate(m_Moon.GetModelMatrix(), glm::vec3(sin(Time)*10.0f, 0.0f, cos(Time)*10.0f));
		m_Moon.GetModelMatrix() = glm::rotate(m_Moon.GetModelMatrix(), glm::radians(Time*20.0f), glm::vec3(0.0f, 1.0f, 0.2f));

	}

	void Application::Render()
	{
		Renderer::Get()->Draw();

		m_Earth.Render(m_Test, m_Camera);
		m_Moon.Render(m_Test, m_Camera);
		m_UI->Render(); //Rendering UI Eelemts.
		m_Window->WindowUpdate();
	}
};