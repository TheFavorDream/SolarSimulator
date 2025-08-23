#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Uranus : public Entity
	{
	public:

		Uranus(std::string pModelPath, std::string pShaderPath);
		~Uranus();

		void Render(Camera& pCamera) override;

	private:

	};
};

