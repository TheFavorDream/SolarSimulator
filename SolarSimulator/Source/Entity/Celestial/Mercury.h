#pragma once
#include "../Entity.h"

#include <string>


namespace Simulator
{

	class Mercury : public Entity
	{
	public:

		Mercury(std::string pModelPath, uint32 pShader);
		~Mercury();

		void Render() override;

	private:
		Texture2D m_Texture;
		float Radius = 20.0f;
	};
};
