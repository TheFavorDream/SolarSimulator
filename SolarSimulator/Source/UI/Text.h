#pragma once

#include "../Core.h"
#include "Element.h"

namespace Simulator
{
	class Text : public Element
	{
	public:

		void Text(const std::string& pID, std::string pText, ImVec2 pPosition)
		{
			m_ID = pID;
			m_Text = pText;
			m_Position = pPosition;
		}

		void Render() override
		{
			ImGui::SetCursorPos(m_Position);
			ImGui::Text(m_Text.c_str());
		}

	private:
		std::string m_Text;
	};
};