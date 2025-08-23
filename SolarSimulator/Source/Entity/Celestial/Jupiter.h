#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Jupiter : public Entity
	{
	public:

		Jupiter(std::string pModelPath, std::string pShaderPath);
		~Jupiter();

		void Render(Camera& pCamera) override;

	private:

	};
};

