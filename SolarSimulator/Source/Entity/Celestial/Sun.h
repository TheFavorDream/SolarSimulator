#pragma once



#include <string>
#include "../Entity.h"

namespace Simulator
{
	class Sun : public Entity
	{
	public:


		 Sun(std::string pModelPath, uint32 pShader);
		~Sun();

		void Render() override;




	private:
		Texture2D m_SunTexture;
	};
};
