#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Neptone : public Entity
	{
	public:

		Neptone(std::string pModelPath, std::string pShaderPath);
		~Neptone();

		void Render(Camera& pCamera) override;

	private:

	};
};

