/*


	Created by Pooya Alizadeh AKA TheVoltage
	Purpose: 
		the main class for ui managment with Imgui as ui library.
*/


#pragma once
#include "../Core.h"
#include "../LogSys/Log.h"
#include "../Window/Window.h"
#include "../../3rdParty/imgui/imgui.h"
#include "../../3rdParty/imgui/imgui_impl_glfw.h"
#include "../../3rdParty/imgui/imgui_impl_opengl3.h"

#include "UIWindow.h"

#include <vector>
#include <unordered_map>

namespace Simulator
{
	class UI
	{
	public:

		 UI();
		~UI();

		int Init();
		int Shutdown();

		void Event();
		void Render();


		int CreateWindowWidget(std::string pKey, ImVec2 pSize = ImVec2(0.0f, 0.0f), ImVec2 pPosition = ImVec2(0.0f, 0.0f));
		int SetWindowRenderState(std::string pKey, bool pShouldRender);
		UIWindow& GetWindow(std::string pKey);

		inline bool IsUsingKeyBoard() { return m_IsUsingKeyboard; }
		inline bool IsUsingMouse() { return m_IsUsingMouse; }

	public:
		static UI* Self();
		static UI* CreateUIInstance();
	private:

		bool m_IsUsingKeyboard = false;
		bool m_IsUsingMouse = false;

		std::unordered_map<std::string, UIWindow> m_Windows;

	private:
		static UI* s_Self;
		const char* m_GLSLVersion = "#version 330";
	};
};
