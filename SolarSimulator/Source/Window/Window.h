#pragma once

#include "Core.h"
#include "LogSys/Log.h"
#include "glfw/glfw3.h"
#include <iostream>

namespace Simulator
{

	class Window
	{
	public:

		Window(uint32 pWidth, uint32 pHeight, const int8* pTitle);
		~Window();

		int Init();
		int ShutDown();


		void SetWindowSize(uint32 pWidth, uint32 pHeight);
		void GetWidnowSize(uint32* pWidth, uint32* pHeight);

		void WindowUpdate();

		inline bool ShouldWindowClose() { return !glfwWindowShouldClose(m_Window);}
		inline uint32 GetWidth() { return m_Width; }
		inline uint32 GetHeigt() { return m_Height; }


	private:
		int OpenWindow();
		int CloseWindow();

	public: 

		static Window* CreateWindowObject(uint32 pWidth, uint32 pHeight, const int8* pTitle);
		static Window* GetWindowInstance();

	private:
		uint32 m_Width, m_Height;
		const int8* m_Title;
		GLFWwindow* m_Window;
	private:
		static Window* s_Self;
	};

	typedef Window* WINDOW;
};