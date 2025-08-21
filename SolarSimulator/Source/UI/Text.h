#pragma once

#include "../Core.h"
#include "Element.h"
#include <string>

namespace Simulator
{
	class Text : public Element
	{
	public:

		Text(const std::string& pID, const std::string& pText, ImVec2 pPosition)
		{
			m_ID = pID;
			m_Text = pText;
			m_Position = pPosition;
		}

		~Text()
		{

		}

		void Render() override
		{
			ImGui::SetCursorPos(m_Position);
			ImGui::Text(m_Text.c_str());
		}

		std::string& GetText() { return m_Text; }
		void SetText(std::string pText)
		{
			m_Text = pText;
		}
	private:
		std::string m_Text;
	};
};