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
	}

	Renderer::~Renderer()
	{
		Log::GetSelf()->SetInfo("Renderer Destructed");
	}

	void Renderer::Draw()
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
};