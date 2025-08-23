#include "Renderer.h"


namespace Simulator
{
	Renderer* Renderer::s_Self = NULL;


	Renderer * Renderer::Get()
	{
		if (!s_Self)
		{
			s_Self = new Renderer;
		}
		return s_Self;
	}

	Renderer::Renderer()
	{
		Log::GetSelf()->SetInfo("Renderer Constructed");
		if (glewInit() > 0)
		{
			Log::GetSelf()->SetError("Unable to Init Glew");
		}
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	Renderer::~Renderer()
	{
		Log::GetSelf()->SetInfo("Renderer Destructed");

		for (auto &i : m_RenderQueue)
		{
			delete i;
		}
	}

	void Renderer::Draw(Camera& pCamera)
	{
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z,  1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (auto &i : m_RenderQueue)
		{
			i->Render(pCamera);
		}

	}

	void Renderer::NewEntity(Entity * pEntity)
	{
		m_RenderQueue.push_back(pEntity);
	}

	void Renderer::SetClearColor(glm::vec3 & pClearColor)
	{
		m_ClearColor = pClearColor;
	}
	void Renderer::SetClearColor(float pR, float pG, float pB)
	{
		SetClearColor(glm::vec3(pR, pG, pB));
	}
};