#include "Sun.h"

namespace Simulator
{
	Sun::Sun(std::string pModelPath, std::string pShaderPath)
	{
		m_Model.LoadModel(pModelPath);
		m_Shader.CreateShader(pShaderPath);


		m_Model.GetModelMatrix() = glm::scale(m_Model.GetModelMatrix(), glm::vec3(8.0f));
	}

	Sun::~Sun()
	{

	}

	void Sun::Render(Camera & pCamera)
	{
		m_Model.Render(m_Shader, pCamera);
	}
};