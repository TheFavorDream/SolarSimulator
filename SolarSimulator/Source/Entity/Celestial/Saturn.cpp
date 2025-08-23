#include "Saturn.h"


namespace Simulator
{
	Saturn::Saturn(std::string pModelPath, std::string pRingPath, std::string pShaderPath)
	{
		m_Model.LoadModel(pModelPath);
		m_Ring.LoadModel(pRingPath);
		m_Shader.CreateShader(pShaderPath);

		m_Position = glm::vec3(0.0f, 0.0f, 60.0f);
	}

	Saturn::~Saturn()
	{
	}

	void Saturn::Render(Camera & pCamera)
	{
		m_Model.GetModelMatrix() = glm::mat4(1.0f);
		m_Model.GetModelMatrix() = glm::scale(m_Model.GetModelMatrix(), glm::vec3(2.0f));
		m_Model.GetModelMatrix() = glm::translate(m_Model.GetModelMatrix(), m_Position);

		m_Ring.GetModelMatrix() = glm::mat4(1.0f);
		m_Ring.GetModelMatrix() = glm::scale(m_Ring.GetModelMatrix(), glm::vec3(4.0f, 0.1f, 4.0f));
		m_Ring.GetModelMatrix() = glm::translate(m_Ring.GetModelMatrix(), m_Position);

		m_Model.Render(m_Shader, pCamera);
		m_Ring.Render(m_Shader, pCamera);
	}
};