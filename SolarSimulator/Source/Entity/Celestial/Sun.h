#pragma once



#include <string>
#include "../Entity.h"

namespace Simulator
{
	class Sun : public Entity
	{
	public:
		static Entity* Construct(std::string pModelPath, uint32 pShader);
	
	public:

		 Sun() = default;
		 Sun(std::string pModelPath, uint32 pShader);
		~Sun();


		void Setup(std::string pModelPath, uint32 pShader);
		void Render() override;




	private:
		Texture2D m_SunTexture;
	};
};
