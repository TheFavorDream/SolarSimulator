#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Uranus : public Entity
	{
	public:

		Uranus(std::string pModelPath, uint32 pShader);
		~Uranus();

		void Render() override;

	private:
		Texture2D m_Texture;
		float Radius = 100.0f;
	};
};

