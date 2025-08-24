#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Neptone : public Entity
	{
	public:

		Neptone(std::string pModelPath, uint32 pShader);
		~Neptone();

		void Render() override;

	private:
		Texture2D m_Texture;
		float Radius = 140.0f;
	};
};

