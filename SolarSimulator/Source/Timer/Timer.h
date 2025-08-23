#pragma once

#include "../Core.h"
#include "../LogSys/Log.h"
#include <chrono>
#include <vector>
#include "../../3rdParty/glfw/include/GLFW/glfw3.h"

typedef std::chrono::high_resolution_clock::time_point  Time;

namespace Simulator
{

	class Timer
	{
	public:
		Timer();
		double GetTime();

	public:
		static int GetElepsedTime();
	private:
		Time m_LastTime;
	public:
		static float s_DeltaTime;

	};

};