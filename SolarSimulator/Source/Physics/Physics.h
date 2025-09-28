
#pragma once
#include "../Core.h"
#include "../LogSys/Log.h"
#include "../Entity/Entity.h"
#include "Properties.h"
#include "../Timer/Timer.h"
#include "../../3rdParty/glfw/include/GLFW/glfw3.h"

#include <math.h>
#include <vector>


namespace Simulator
{

	class Physics
	{
	public:

		Physics();
		~Physics();

		void Update();
		void PushProperty(Properties* pProp);
		float CalculateForce(const Properties* pObj1, const Properties* pObj2);

	public:
		static Physics* Get();
	private:


	private:
		std::vector<Properties*> m_Objects;
		static Physics* s_Self;
	};

};