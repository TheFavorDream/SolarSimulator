#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Venus : public Entity
	{
	public:

		Venus(std::string pModelPath, uint32 pShader);
		~Venus();

		void Render() override;

	private:
		Texture2D m_Texture;
		float Radius = 30.0f;
	};
};

