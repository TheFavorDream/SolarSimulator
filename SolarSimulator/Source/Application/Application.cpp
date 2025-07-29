#include "Application.h"



namespace Simulator
{
	Application::Application(const int pWidth, const int pHeight, const char * pTitle)
	{
		m_Log.SetInfo("Application Started");
		m_Window = Window::CreateWindowObject(pWidth, pHeight, pTitle);
		Renderer::Get(); // To Allocate memory
		Setup();
	}
	Application::~Application()
	{
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

		Model = glm::scale(Model, glm::vec3(0.5f));
	}
	void Application::Input()
	{
		glfwPollEvents();
	}

	void Application::Update()
	{
		Model = glm::rotate(Model, glm::radians(0.01f), glm::vec3(0.0f, 0.0f, 1.0f));
		m_Test.SetUniformMat4("Model", Model);
	}

	void Application::Render()
	{
		Renderer::Get()->Draw();
		Triangle.Render(m_Test);
		m_Window->WindowUpdate();
	}
};