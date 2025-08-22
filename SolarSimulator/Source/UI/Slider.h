#pragma once

#include "../Core.h"
#include "Element.h"
#include "../../3rdParty/imgui/imgui.h"

namespace Simulator
{

	class SliderF : public Element
	{
	public:

		SliderF(const std::string& pTitle, float pMin, float pMax, ImVec2 pPosition)
		{
			if (pMax < pMin) // Swap the values if pMax was greater that pMin
			{
				std::swap(pMin, pMax);
			}

			m_Max = pMax;
			m_Min = pMin;

			m_ID = pTitle;
			m_Position = pPosition;
		}


		void Render() override
		{
			ImGui::SetCursorPos(m_Position);
			ImGui::SliderFloat(m_ID.c_str(), &m_Value, m_Min, m_Max);
		}

		inline float& GetValue() { return m_Value; }
		inline float GetMin() { return m_Min; }
		inline float GetMax() { return m_Max; }
		
		void SetMax(float pMax) 
		{
		
			if (pMax <= m_Min)
			{
				assert(pMax <= m_Min && "Bad stuff happend");
				return;
			}
			m_Max = pMax;
		}

		void SetMin(float pMin)
		{

			if (pMin >= m_Max)
			{
				assert(pMin >= m_Max && "Bad stuff happend");
				return;
			}
			m_Min = pMin;
		}

		void SetValue(float pValue)
		{
			m_Value = pValue;
		}

	private:
		float m_Value = 0.0f;
		float m_Max = 0.0f;
		float m_Min = 0.0f;
	};



	class SliderI : public Element
	{
	public:
		SliderI(const std::string& pTitle, int pMin, int pMax, ImVec2 pPosition)
		{
			if (pMax < pMin) // Swap the values if pMax was greater that pMin
			{
				std::swap(pMin, pMax);
			}

			m_Max = pMax;
			m_Min = pMin;

			m_ID = pTitle;
			m_Position = pPosition;
		}


		void Render() override
		{
			ImGui::SetCursorPos(m_Position);
			ImGui::SliderInt(m_ID.c_str(), &m_Value, m_Min, m_Max);
		}

		inline int GetValue() { return m_Value; }
		inline int GetMin() { return m_Min; }
		inline int GetMax() { return m_Max; }

		void SetMax(int pMax)
		{

			if (pMax <= m_Min)
			{
				assert(pMax <= m_Min && "Bad stuff happend");
				return;
			}
			m_Max = pMax;
		}

		void SetMin(int pMin)
		{

			if (pMin >= m_Max)
			{
				assert(pMin >= m_Max && "Bad stuff happend");
				return;
			}
			m_Min = pMin;
		}

		void SetValue(int pValue)
		{
			m_Value = pValue;
		}

	private:
		int m_Value = 0.0f;
		int m_Max = 0.0f;
		int m_Min = 0.0f;
	};

};