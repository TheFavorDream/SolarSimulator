/*

	Created by Pooya Alizadeh (TheVoltage)
	Purpose:
		takes care of Rendering process
*/

#include "Core.h"
#include "LogSys/Log.h"
#include "GL/glew.h"
#include "../3rdParty/glm/glm.hpp"

namespace Simulator
{
	class Renderer
	{
	public:

		Renderer();
		~Renderer();

		void Draw();

		void SetClearColor(glm::vec3& pClearColor);
		void SetClearColor(float pR, float pG, float pB);


	public:
		static Renderer* Get();
	private:
		glm::vec3 m_ClearColor = glm::vec3(0.0f);
	private:
		static Renderer* s_Self;
	};
};
