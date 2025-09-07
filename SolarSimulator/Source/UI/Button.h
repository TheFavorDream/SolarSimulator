#pragma once
#include "Element.h"
#include "../LogSys/Log.h"
#include "../../3rdParty/imgui/imgui.h"

namespace Simulator
{
	class Button : public Element
	{
	public:
		Button(const std::string& pTitle, ImVec2 pSize, ImVec2 pPosition)
		{
			m_ID = pTitle;
			m_Size = pSize;
			m_Position = pPosition;
		}

		void Render() override
		{
			ImGui::SetCursorPos(m_Position);
			m_State = ImGui::Button(m_ID.c_str(), m_Size);
		}

		 bool GetState() const 
		 {
			 return m_State;
		 }

	private:
		bool m_State=false;
	};
};