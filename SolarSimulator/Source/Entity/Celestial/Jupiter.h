#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Jupiter : public Entity
	{
	public:

		Jupiter(std::string pModelPath, uint32 pShader);
		~Jupiter();

		void Render() override;


	private:
		Texture2D m_Texture;
		float Radius = 60.0f;
	};
};

