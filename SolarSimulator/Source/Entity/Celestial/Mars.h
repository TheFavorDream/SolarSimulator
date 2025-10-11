#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Mars : public Entity
	{
	public:

		Mars(std::string pModelPath, uint32 pShader);
		~Mars();

		void Render() override;

	private:
		Texture2D m_Texture;
		float Radius = 50.0f;
	};
};

