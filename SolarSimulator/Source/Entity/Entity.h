
#pragma once
#include "../Renderer/Shader.h"
#include "../Camera/Camera.h"
#include "../Renderer/Texture.h"
#include "../LogSys/Log.h"
#include "../Core.h"
#include "../Mesh/Mesh.h"
#include "../Renderer/ShaderManager.h"

namespace Simulator
{

	class Entity
	{
	public:

		Entity();
		virtual ~Entity();

		virtual void Render() = 0;

		inline glm::vec3& GetPosition() { return m_Position; }

	protected:
		glm::vec3 m_Position;
		Mesh m_Mesh;
		uint32 m_Shader;
	};

};