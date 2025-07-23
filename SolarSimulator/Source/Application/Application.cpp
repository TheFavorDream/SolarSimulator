#include "Application.h"
#include "Application.h"
#include "Application.h"

namespace Simulator
{
	Application::Application(const int pWidth, const int pHeight, const char * pTitle)
	{
		std::cout << "Application Constructed\n";
	}
	Application::~Application()
	{
		std::cout << "Application Destructed\n";
		std::cin.get();
	}
	void Application::Run()
	{
		std::cout << "Application Running\n";
	}
};