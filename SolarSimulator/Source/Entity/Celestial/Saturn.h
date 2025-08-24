#pragma once
#include "../Entity.h"

#include <string>

namespace Simulator
{

	class Saturn : public Entity
	{
	public:

		Saturn(std::string pSpherePath, std::string pRingPath, uint32 pShader);
		~Saturn();

		void Render() override;

	private:
		Mesh m_Ring;
		glm::vec3 m_RingPos;
		Texture2D m_SphereTexture;
		Texture2D m_RingTexture;

		float Radius = 60.0f;
	};
};

