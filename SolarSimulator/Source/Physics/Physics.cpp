#include "Physics.h"


namespace Simulator
{


	Physics* Physics::s_Self = NULL;

	Physics * Physics::Get()
	{

		if (s_Self == NULL)
		{
			s_Self = new Physics();
		}
		return s_Self;
	}

//=====================================================


	Physics::Physics()
	{
		Log::GetSelf()->SetInfo("Physics Engine Started");
	}

	Physics::~Physics()
	{
		Log::GetSelf()->SetInfo("Physics Engine Shutdown");
	}

	//Runs every frame
	void Physics::Update(const std::vector<Entity*>& m_Objects)
	{
		for (auto &i : m_Objects)
		{
			i->GetProperties().Position = glm::vec3(10.0f, 0.0f, 4.0f);

		}
	}

};