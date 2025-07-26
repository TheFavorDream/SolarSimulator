#include "Application.h"


namespace Simulator
{
	Application::Application(const int pWidth, const int pHeight, const char * pTitle)
	{
		m_Log.SetInfo("Application Started");
		m_Window = Window::CreateWindowObject(pWidth, pHeight, pTitle);

		
	}
	Application::~Application()
	{
		delete m_Window;
	}

	void Application::Run()
	{
		while (m_Window->ShouldWindowClose())
		{
			Renderer::Get()->Draw();
			glfwPollEvents();
			m_Window->WindowUpdate();
		}
	}
};