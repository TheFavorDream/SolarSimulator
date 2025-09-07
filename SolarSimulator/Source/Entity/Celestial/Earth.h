#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Earth : public Entity
	{
	public:

		Earth(std::string pModelPath, uint32 pShader);
		~Earth();

		void Render() override;

	private:
		Texture2D m_EarthTexture;
		Texture2D m_EarthClouds;
		Texture2D m_EarthSpecMap;
		Texture2D m_EarthNight;

		float Radius = 30.0f;
	};
};

