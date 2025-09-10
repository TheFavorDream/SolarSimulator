#include "Grid.h"


namespace Simulator
{
	Grid::Grid(uint32 pShader, uint32 pWidth, uint32 pHeight, glm::vec3 pOffset, float pUnitSize)
	{
		m_Shader = pShader;
		m_Width = pWidth;
		m_Height = pHeight;
		m_Offset = pOffset;
		m_UnitSize = pUnitSize;

		Generate();
	}

	Grid::~Grid()
	{
		m_Mesh.Free();
	}


	void Grid::Generate()
	{
		
		std::vector<Vertex> pVerticis;
		std::vector<uint16> pIndicis;

		glm::vec3 StartPos = glm::vec3(0.0f, 0.0f, 0.0f);


		glm::vec3 Rectangle[4] =
		{
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(m_UnitSize, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, m_UnitSize),
			glm::vec3(m_UnitSize, 0.0f, m_UnitSize)
		};

		std::vector<uint16> StartIndicis = { 0, 1, 2, 1, 2, 3 };

		for (int i = 0; i < m_Height; i++)
		{
			for (int h = 0; h < m_Width; h++)
			{
				StartPos = glm::vec3(m_Offset.x+(h*m_UnitSize), m_Offset.y, m_Offset.z + (i*m_UnitSize));
				for (int j = 0; j < 4; j++)
				{
					glm::vec3 Pos;
					Pos = Rectangle[j] + StartPos;
					pVerticis.push_back({ Pos });


				}
				for (int k = 0; k < 6; k++)
				{
					pIndicis.push_back(StartIndicis[k]);
					StartIndicis[k] += 4;
				}
			}
		}
		


		m_Mesh.SetUp(pVerticis, pIndicis);
		m_Mesh.Free();
	}

	void Grid::Render()
	{

		if (!UI::Self()->GetCheckbox("Setter", "Show Grid")->GetState())
			return;


		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		m_Mesh.Render(ShaderManager::Self()->GetShader(m_Shader), GL_TRIANGLES);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		
	}

};