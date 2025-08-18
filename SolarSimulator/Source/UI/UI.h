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
#include "Button.h"
#include "Slider.h"
#include "Text.h"
#include "Checkbox.h"
#include "InputField.h"
#include "Input3F.h"

#include <fstream>
#include <vector>
#include <unordered_map>
#include "../../3rdParty/JsonParser/Json.h"
using Json = nlohmann::json;
namespace Simulator
{
	class UI
	{
	public:

		 UI();
		~UI();

		int Init();
		int Shutdown();

		//This method will read, parse and load a jason file that contains ui al
		int LoadUI(std::string pUIConfig);

		void Event();
		void Render();

		void SetElementRenderingState(std::string pWindowKey, std::string pID, bool pState);

		int CreateWindowWidget(std::string pKey, ImVec2 pSize = ImVec2(0.0f, 0.0f), ImVec2 pPosition = ImVec2(0.0f, 0.0f), bool LockedPos=false);
		int SetWindowRenderState(std::string pKey, bool pShouldRender);
		UIWindow& GetWindow(std::string pKey);

		void CreateButton(std::string pKey, std::string pTitle, ImVec2 pPosition, ImVec2 pSize=ImVec2(60.0f, 20.0f));
		Button* GetButton(std::string pWindowKey, std::string pID);

		void CreateSliderF(std::string pKey, std::string pTitle, float pMax, float pMin, ImVec2 pPosition);
		SliderF* GetSliderF(std::string pWindowKey, std::string pID);

		void CreateSliderI(std::string pKey, std::string pTitle, int pMax, int pMin, ImVec2 pPosition);
		SliderI* GetSliderI(std::string pWindowKey, std::string pID);

		void CreateText(std::string pKey, std::string pID, std::string pText, ImVec2 pPosition);
		Text* GetText(std::string pKey, std::string pID);

		void CreateCheckbox(std::string pKey, std::string pID, bool pDefState, ImVec2 pPosition);
		Checkbox* GetCheckbox(std::string pWindowKey, std::string pID);

		void CreateInputF(std::string pKey, std::string pID, float pDefValue, ImVec2 pPosition);
		InputF* GetInputF(std::string pWindowKey, std::string pID);

		void CreateInput3F(std::string pKey, std::string pID, ImVec2 pPosition, float pDefValue1=0.0f, float pDefValue2=0.0f, float pDefValue3=0.0);
		Input3F* GetInput3F(std::string pWindowKey, std::string pID);

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
