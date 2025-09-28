#pragma once


#include "../Core.h"
#include "../../3rdParty/glm/glm.hpp"
#include "../../3rdParty/glm/vec3.hpp"

namespace Simulator
{
	struct ScientificNotation
	{
		ScientificNotation() = default;
		ScientificNotation(float pCoefficient, int pExponent):
			Coefficient(pCoefficient), Exponent(pExponent){		}


		float GetValue() const
		{
			return Coefficient* pow(10.0f, Exponent);
		}

		float Coefficient = 0.0f;
		int Exponent = 1;
	};

	struct Properties
	{
		ScientificNotation Mass;
		ScientificNotation Radius;
		glm::vec3 Volacity;
		glm::vec3 Position;
	};

};