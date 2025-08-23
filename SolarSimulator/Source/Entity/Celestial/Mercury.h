#pragma once
#include "../Entity.h"

#include <string>


namespace Simulator
{

	class Mercury : public Entity
	{
	public:

		Mercury(std::string pModelPath, std::string pShaderPath);
		~Mercury();

		void Render(Camera& pCamera) override;

	private:

	};
};
