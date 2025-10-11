#include "Entity.h"


namespace Simulator
{

	Entity::Entity()
	{
		m_Position = glm::vec3(0.0f);
	}

	Entity::Entity(std::string pModelPath, uint32 pShader)
	{
		m_Mesh.LoadMesh(pModelPath);
		m_Shader = pShader;
	}

	Entity::~Entity()
	{
		m_Mesh.Free();
	}

	void Entity::Render()
	{
		m_Mesh.Render(ShaderManager::Self()->GetShader(m_Shader));
	}

};