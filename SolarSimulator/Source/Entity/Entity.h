
#pragma once
#include "../Renderer/Shader.h"
#include "../Camera/Camera.h"
#include "../Renderer/Texture.h"
#include "../LogSys/Log.h"
#include "../Core.h"
#include "../Mesh/Mesh.h"
#include "../Renderer/ShaderManager.h"
#include "../Physics/Properties.h"
#include "../Physics/Physics.h"

namespace Simulator
{

	class Entity
	{
	public:

		Entity();
		Entity(std::string pModelPath, uint32 pShader);
		virtual ~Entity();

		virtual void Render();

		inline glm::vec3& GetPosition() { return m_Position; }

		inline Properties& GetProperties() { return m_Properties; }

	protected:
		glm::vec3 m_Position;
		
		Properties m_Properties;
		Mesh m_Mesh;
		uint32 m_Shader;
	};

};