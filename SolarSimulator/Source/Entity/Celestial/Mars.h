#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Mars : public Entity
	{
	public:

		Mars(std::string pModelPath, std::string pShaderPath);
		~Mars();

		void Render(Camera& pCamera) override;

	private:

	};
};

