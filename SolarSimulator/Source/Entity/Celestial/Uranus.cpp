#include "Uranus.h"


namespace Simulator
{
	Uranus::Uranus(std::string pModelPath, std::string pShaderPath)
	{
		m_Model.LoadModel(pModelPath);
		m_Shader.CreateShader(pShaderPath);

		m_Position = glm::vec3(0.0f, 0.0f, 70.0f);
	}

	Uranus::~Uranus()
	{
	}

	void Uranus::Render(Camera & pCamera)
	{
		m_Model.GetModelMatrix() = glm::mat4(1.0f);
		m_Model.GetModelMatrix() = glm::translate(m_Model.GetModelMatrix(), m_Position);

		m_Model.Render(m_Shader, pCamera);
	}
};