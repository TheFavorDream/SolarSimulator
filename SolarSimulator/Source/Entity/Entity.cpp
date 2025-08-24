#include "Entity.h"


namespace Simulator
{

	Entity::Entity()
	{
		m_Position = glm::vec3(0.0f);
	}

	Entity::~Entity()
	{
		m_Mesh.Free();
	}

};