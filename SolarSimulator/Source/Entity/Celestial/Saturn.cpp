#include "Saturn.h"


namespace Simulator
{
	Saturn::Saturn(std::string pModelPath, std::string pRingPath, uint32 pShader)
	{
		m_Mesh.LoadMesh(pModelPath);
		m_Ring.LoadMesh(pRingPath);
		m_Shader = pShader;

		m_Position = glm::vec3(0.0f, 0.0f, 60.0f);
		m_RingPos = glm::vec3(0.0f, 0.0f, 30.0f);

		m_SphereTexture.CreateTexture(std::string(ASSETS_PARENT_DIR) + "Saturn.jpg", GL_LINEAR, GL_LINEAR, false);
		m_RingTexture.CreateTexture(std::string(ASSETS_PARENT_DIR) + "Ring.png", GL_LINEAR, GL_LINEAR, false);
	}

	Saturn::~Saturn()
	{
	}

	void Saturn::Render()
	{
		float Time = (float)glfwGetTime()*0.04f;
		m_Position = glm::vec3(sin(Time)*Radius, 0.0f, cos(Time)*Radius);
		m_RingPos = glm::vec3(sin(Time)*Radius/2.0f, 0.0f, cos(Time)*Radius/2.0f);

		m_Mesh.GetModelMatrix() = glm::mat4(1.0f);
		m_Mesh.GetModelMatrix() = glm::scale(m_Mesh.GetModelMatrix(), glm::vec3(2.0f));
		m_Mesh.GetModelMatrix() = glm::translate(m_Mesh.GetModelMatrix(), m_Position);

		m_Ring.GetModelMatrix() = glm::mat4(1.0f);
		m_Ring.GetModelMatrix() = glm::scale(m_Ring.GetModelMatrix(), glm::vec3(4.0f, 0.1f, 4.0f));
		m_Ring.GetModelMatrix() = glm::translate(m_Ring.GetModelMatrix(), m_RingPos);

		m_SphereTexture.Bind();
		m_Mesh.Render(ShaderManager::Self()->GetShader(m_Shader) );
		m_SphereTexture.Unbind();


		m_RingTexture.Bind();
		m_Ring.Render(ShaderManager::Self()->GetShader(m_Shader) );
		m_RingTexture.Unbind();
	}
};