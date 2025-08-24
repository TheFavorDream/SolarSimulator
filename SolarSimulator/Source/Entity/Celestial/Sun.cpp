#include "Sun.h"

namespace Simulator
{
	Sun::Sun(std::string pModelPath, uint32 pShader)
	{
		m_Shader = pShader;
		m_Mesh.LoadMesh(pModelPath);
		m_SunTexture.CreateTexture(std::string(ASSETS_PARENT_DIR) + "Sun.jpg", GL_LINEAR, GL_LINEAR, false);
	}

	Sun::~Sun()
	{

	}

	void Sun::Render()
	{

		m_Mesh.GetModelMatrix() = glm::mat4(1.0f);
		m_Mesh.GetModelMatrix() = glm::scale(m_Mesh.GetModelMatrix(), glm::vec3(8.0f));
		m_Mesh.GetModelMatrix() = glm::translate(m_Mesh.GetModelMatrix(), m_Position);

		m_SunTexture.Bind(0);
		ShaderManager::Self()->BindShader(m_Shader);
		ShaderManager::Self()->GetShader(m_Shader).SetUniformInt1("Texture", 0);
		m_Mesh.Render(ShaderManager::Self()->GetShader(m_Shader));
	}
};