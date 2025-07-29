#include "Window.h"


namespace Simulator
{

	Window* Window::s_Self = NULL;

	Window* Window::CreateWindowObject(uint32 pWidth, uint32 pHeight, const int8 * pTitle)
	{
		if (!s_Self)
		{
			s_Self = new Window(pWidth, pHeight, pTitle);
		}
		return s_Self;
	}

	Window* Window::GetWindowInstance()
	{
		return s_Self;
	}


	Window::Window(uint32 pWidth, uint32 pHeight, const int8 * pTitle)
		: m_Width(pWidth), m_Height(pHeight), m_Title(pTitle)
	{
		Init();
		OpenWindow();
	}

	Window::~Window()
	{
		CloseWindow();
		ShutDown();
	}

	int Window::Init()
	{
		if (glfwInit() == GLFW_FALSE)
		{
			Log::GetSelf()->SetError("Unable to Init GLFW");
			return 1;
		}
		return 0;
	}

	int Window::ShutDown()
	{
		glfwTerminate();
		return 0;
	}

	void Window::SetWindowSize(uint32 pWidth, uint32 pHeight)
	{
		glfwSetWindowSize(m_Window, pWidth, pHeight);
	}

	void Window::GetWidnowSize(uint32 * pWidth, uint32 * pHeight)
	{
		glfwGetWindowSize(m_Window, (int*)(pWidth), (int*)(pHeight));
	}

	void Window::WindowUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwGetWindowSize(m_Window, (int*)&m_Width, (int*)&m_Height);
		glViewport(0, 0, m_Width, m_Height);
	}

	int Window::OpenWindow()
	{
		m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
		if (!m_Window)
		{
			Log::GetSelf()->SetError("Unable to Create A window");

			return 1;
		}
		glfwMakeContextCurrent(m_Window);
		return 0;
	}

	int Window::CloseWindow()
	{
		glfwDestroyWindow(m_Window);
		if (m_Window == NULL)
		{
			Log::GetSelf()->SetInfo("Window Got Destroyed");
		}
		else
		{
			Log::GetSelf()->SetWarning("Unable to Destroy the Window");
		}
		return 0;
	}


};