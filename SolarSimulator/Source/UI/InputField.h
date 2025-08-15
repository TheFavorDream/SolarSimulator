#pragma once
#include "Element.h"
#include "../Core.h"


namespace Simulator
{
	class InputF : public Element
	{
	public:
		InputF(std::string& pID, ImVec2 pPosition, float pDefValue)
		{
			m_ID = pID;
			m_Position = pPosition;
			m_Value = pDefValue;
		}

		void Render() override
		{
			ImGui::SetCursorPos(m_Position);
			ImGui::InputFloat(m_ID.c_str(), &m_Value);
		}
		
		inline float& GetValue() { return m_Value; }

	private:
		float m_Value;
	};
}