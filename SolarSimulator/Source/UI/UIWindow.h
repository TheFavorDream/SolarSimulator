#pragma once

#include "../Core.h"
#include "../LogSys/Log.h"
#include "../../3rdParty/imgui/imgui.h"
#include "Element.h"

#include <unordered_map>

namespace Simulator
{
	class UIWindow
	{
	public:

		 UIWindow() = default;
		 UIWindow(const std::string& pTitle, ImVec2 pSize=ImVec2(0.0f, 0.0f), ImVec2 pPosition= ImVec2(0.0f, 0.0f), bool pLockedPos=false);
		~UIWindow();


		void Render();

		void SetWindowSize(ImVec2 pSize);
		void SetWindowPosition(ImVec2 pPosition);
		void SetWindowTitle(std::string pTitle);


		void EnableRender() { m_Render = true; }
		void DisableRender() { m_Render = false; }
		void SetShouldRender(bool pRender) { m_Render = pRender; }

		void NewElement(Element* pElement);

		Element* GetElement(std::string pID);

		inline bool ShouldRender() { return m_Render; }


	private:
		ImGuiWindowFlags GetWindowFlags();
	private:


		std::unordered_map<std::string, Element*> m_Elements;

		ImVec2 m_Position;
		ImVec2 m_Size;
		std::string m_Title;


		//Window Properties:
		bool m_Render = true;
		bool m_NoTitleBar = false;
		bool m_LockedSize = false;
		bool m_LockedPosition = false;
		bool m_NoScrollbar = false;
		bool m_AlwaysAutoResize = false;
		bool m_Collapsable = true;
	};
};