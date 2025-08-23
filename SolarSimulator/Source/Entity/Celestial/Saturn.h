#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Saturn : public Entity
	{
	public:

		Saturn(std::string pSpherePath, std::string pRingPath, std::string pShaderPath);
		~Saturn();

		void Render(Camera& pCamera) override;

	private:
		Model m_Ring;
	};
};

