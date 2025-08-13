#pragma once
#include "../Core.h"
#include "../LogSys/Log.h"

#include "../../3rdParty/imgui/imgui.h"
#include "Element.h"


namespace Simulator
{
	class Checkbox : public Element
	{
	public:

		Checkbox(std::string pID, ImVec2 pPosition, bool pDefState)
		{
			m_Position = pPosition;
			m_ID = pID;
			m_State = pDefState;
		}

		void Render() override
		{
			ImGui::SetCursorPos(m_Position);
			ImGui::Checkbox(m_ID.c_str(), &m_State);
		}

		bool& GetState() { return m_State; }

	private:
		bool m_State;
	};
};

