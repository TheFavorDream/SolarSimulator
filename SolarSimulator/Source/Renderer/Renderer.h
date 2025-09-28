/*

	Created by Pooya Alizadeh (TheVoltage)
	Purpose:
		takes care of Rendering process
*/
#pragma once
#include "Core.h"
#include "LogSys/Log.h"
#include "GL/glew.h"
#include "../3rdParty/glm/glm.hpp"
#include "../Entity/Entity.h"
#include "../Timer/Timer.h"
#include "../Camera/Camera.h"


#define SUN     0
#define MERCURY 1
#define VENUS   2
#define EARTH   3
#define MARS    4
#define JUPITER 5
#define SATURN  6
#define URANUS  7
#define NEPTONE 8

namespace Simulator
{
	class Renderer
	{
	public:

		Renderer();
		~Renderer();

		void Draw();

		void NewEntity(Entity* pEntity);

		void SetClearColor(glm::vec3& pClearColor);
		void SetClearColor(float pR, float pG, float pB);


		void ClearDefFrameBuffer();

		Entity* operator[](uint32 pKey);


		inline const std::vector<Entity*> GetEntities() { return m_RenderQueue; }

	public:
		static Renderer* Get();
	private:
		glm::vec3 m_ClearColor = glm::vec3(0.0f);
		std::vector<Entity*> m_RenderQueue;
	private:
		static Renderer* s_Self;
	};
};
