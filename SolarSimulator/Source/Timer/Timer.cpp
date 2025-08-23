#include "Timer.h"


namespace Simulator
{
	float Timer::s_DeltaTime = 0.0f;


	Timer::Timer()
	{
		m_LastTime = std::chrono::high_resolution_clock::now();
	}

	double Timer::GetTime()
	{

		Time Current = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> Duration = Current - m_LastTime;
		m_LastTime = Current;

		return std::chrono::duration_cast<std::chrono::milliseconds>(Duration).count();
	}

	int Timer::GetElepsedTime()
	{
		return glfwGetTime();
	}

};