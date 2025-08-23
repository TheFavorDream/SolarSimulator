
#pragma once
#include "../Renderer/Shader.h"
#include "../Camera/Camera.h"
#include "../LogSys/Log.h"
#include "../Core.h"
#include "../Mesh/Model.h"

namespace Simulator
{

	class Entity
	{
	public:

		Entity();
		virtual ~Entity();

		virtual void Render(Camera& pCamera) = 0;


		inline glm::vec3 GetPosition() { return m_Position; }

	protected:
		glm::vec3 m_Position;
		Model m_Model;
		Shader m_Shader;
	};

};