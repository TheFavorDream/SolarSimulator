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




	void Application::Setup()
	{
		m_Test.CreateShader("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Shaders\\basic.glsl");
		Triangle.SetUp(Vertices, Indices);
		m_Texture.CreateTexture("C:\\Users\\TheVoltage\\Desktop\\SolarSimulator\\SolarSimulator\\Resources\\Asset\\container.png");
		Model = glm::scale(Model, glm::vec3(0.5f));


		m_UI->CreateWindowWidget("Window");
		m_UI->CreateButton("Window", "Button", ImVec2(10.0f, 25.0f));
		m_UI->CreateSliderF("Window", "SliderF", 2.0f, 0.0f, ImVec2(10.0f, 50.0f));
		m_UI->CreateSliderI("Window", "SliderI", 20, 0, ImVec2(10.0f, 70.0f));
	}
	void Application::Input()
	{
		m_Camera.HandleCameraMovement();
		m_Camera.HandleMouseMovement();
		m_UI->Event();//UI Events
		glfwPollEvents();
	}

	void Application::Update()
	{
		Model = glm::rotate(Model, glm::radians(0.01f), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Test.SetUniformMat4("Model", Model);

		if (m_UI->GetButton("Window", "Button")->GetState())
		{
			Log::GetSelf()->SetInfo("Slider Vlaue:%f", m_UI->GetSliderF("Window", "SliderF")->GetValue());
		}
	}

	void Application::Render()
	{
		Renderer::Get()->Draw();
		m_Texture.Bind(0);
		Triangle.Render(m_Test, m_Camera);

		m_UI->Render(); //Rendering UI Eelemts.
		m_Window->WindowUpdate();
	}
};