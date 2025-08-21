#pragma once
#include "../Core.h"
#include "../../3rdParty/imgui/imgui.h"
#include "../LogSys/Log.h"
#include <string>

namespace Simulator
{
	class Element
	{
	public:

		virtual void Render() {};

		inline ImVec2 GetPosition() { return m_Position; }
		inline ImVec2 GetSize() { return m_Size; }
		inline const std::string& GetID() { return m_ID; }

		bool& GetRenderState() { return m_Render; }

	protected:
		ImVec2 m_Position;
		ImVec2 m_Size;
		std::string m_ID;
		bool m_Render = true;
	};
};