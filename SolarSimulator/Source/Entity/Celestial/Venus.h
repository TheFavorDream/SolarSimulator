#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Venus : public Entity
	{
	public:

		Venus(std::string pModelPath, std::string pShaderPath);
		~Venus();

		void Render(Camera& pCamera) override;

	private:

	};
};

