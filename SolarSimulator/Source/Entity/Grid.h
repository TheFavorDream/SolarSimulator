#include "Entity.h"

namespace Simulator
{

	class Grid : public Entity
	{
	public:
		
		Grid(uint32 pShader, uint32 pWidth, uint32 pHeight, glm::vec3 pOffset, float pUnitSize=8.0f);
		~Grid();

		//This function generates the main grid (call in setup)
		void Generate();
		void Render() override;
	private:
		uint32 m_Width;
		uint32 m_Height;
		float  m_UnitSize;
		glm::vec3 m_Offset;
	};

};

