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
	void Physics::Update()
	{
		uint32 Size = m_Objects.size();



		for (uint32 i = 0; i < Size; i++)
		{
			for (uint32 j = i + 1; j < Size; j++)
			{
				float Force = CalculateForce(m_Objects[i], m_Objects[j]);
				//Log::GetSelf()->SetInfo("Force Value: %f", Force);
				//m_Objects[j]->Volacity.x += (Force / m_Objects[j]->Mass.GetValue());
				//m_Objects[i]->Volacity.x -= (Force / m_Objects[i]->Mass.GetValue());
			}
		}
	}

	void Physics::PushProperty(Properties* pProp)
	{
		m_Objects.push_back(pProp);
	}

	float Physics::CalculateForce(const Properties* pObj1, const Properties* pObj2)
	{
		return (pObj1->Mass.GetValue()*pObj2->Mass.GetValue()) / pow((abs(pObj1->Position.x) + abs(pObj2->Position.x)), 2.0f);
	}

};