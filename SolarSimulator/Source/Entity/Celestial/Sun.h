#pragma once



#include <string>
#include "../Entity.h"

namespace Simulator
{
	class Sun : public Entity
	{
	public:


		 Sun(std::string pModelPath, std::string pShaderPath);
		~Sun();

		void Render(Camera& pCamera) override;


	private:

	};
};
