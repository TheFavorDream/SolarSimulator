#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Earth : public Entity
	{
	public:

		Earth(std::string pModelPath, std::string pShaderPath);
		~Earth();

		void Render(Camera& pCamera) override;

	private:

	};
};

