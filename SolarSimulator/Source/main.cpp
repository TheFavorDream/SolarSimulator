/*

	Created and Developed by Pooya Alizadeh (aka TheVoltage)

	Purpose:
		SolarSimulator is a computer program designed to run on windows (at least for now) for simulating our solar system 
		and mainly The Universal Gravity Law.
		Made with C++ and OpenGL as well as some other libraries like glfw and etc.
*/

#include "Application/Application.h"

int main(int argc, char** arvg)
{
	Simulator::Application* App = new Simulator::Application(1000, 500, "Solar Simulator");
	App->Run();
	delete App;
	return 0;
}
