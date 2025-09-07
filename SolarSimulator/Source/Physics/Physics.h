
#pragma once
#include "../Core.h"
#include "../LogSys/Log.h"
#include "../Entity/Entity.h"
#include "Properties.h"
#include "../Timer/Timer.h"

#include <math.h>
#include <vector>


namespace Simulator
{

	class Physics
	{
	public:

		Physics();
		~Physics();

		void Update(const std::vector<Entity*>& m_Objects);

		inline glm::vec3 GetAcceleration(ScientificNotation pForce, ScientificNotation pMass)
		{

		}

	public:
		static Physics* Get();
	private:


	private:
		static Physics* s_Self;
	};

};