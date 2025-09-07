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
			i->GetProperties().Position += (i->GetProperties().Volacity * Timer::s_DeltaTime);
			i->GetProperties().Volacity += glm::vec3(0.0f, 0.0f, -0.00001f);

			if (i->GetProperties().Position.z <= -100.0f || i->GetProperties().Position.z >= 100.0f)
			{
				i->GetProperties().Volacity *= -1;
			}

		}
	}

};