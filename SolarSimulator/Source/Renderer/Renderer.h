/*

	Created by Pooya Alizadeh (TheVoltage)
	Purpose:
		takes care of Rendering process
*/

#include "Core.h"
#include "LogSys/Log.h"
#include "GL/glew.h"


namespace Simulator
{
	class Renderer
	{
	public:

		Renderer();
		~Renderer();

		void Draw();

	public:
		static Renderer* Get();
	private:

	private:
		static Renderer* s_Self;
	};
};
