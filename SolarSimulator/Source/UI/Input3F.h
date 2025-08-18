#pragma once
#include "Element.h"
#include "../Core.h"



namespace Simulator
{

	class Input3F : public Element
	{
	public:

		Input3F(std::string& pID, ImVec2 pPosition, float pDefValue1, float pDefValue2, float pDefValue3)
		{
			m_Position = pPosition;
			m_ID = pID;
			m_Value[0] = pDefValue1;
			m_Value[1] = pDefValue2;
			m_Value[2] = pDefValue3;
		}

		void Render() override
		{
			ImGui::SetCursorPos(m_Position);
			ImGui::InputFloat3(m_ID.c_str(), m_Value);
		}

		inline float GetValue1() { return m_Value[0]; }
		inline float GetValue2() { return m_Value[1]; }
		inline float GetValue3() { return m_Value[2]; }


	private:
		float m_Value[3] = {0.0f, 0.0f, 0.0f};
	};
};