#include "Venus.h"


namespace Simulator
{
	Venus::Venus(std::string pModelPath, uint32 pShader)
	{
		m_Mesh.LoadMesh(pModelPath);

		m_Shader = pShader;

		m_Position = glm::vec3(0.0f, 0.0f, 30.0f);
		m_Texture.CreateTexture(std::string(ASSETS_PARENT_DIR) + "Venus.jpg", GL_LINEAR, GL_LINEAR, false);
		ShaderManager::Self()->GetShader(m_Shader).SetUniformInt1("Texture", 0);
	}

	Venus::~Venus()
	{
	}

	void Venus::Render()
	{
		float Time = (float)glfwGetTime()*0.08f;
		m_Position = glm::vec3(sin(Time)*Radius, 0.0f, cos(Time)*Radius);
		m_Mesh.GetModelMatrix() = glm::mat4(1.0f);
		m_Mesh.GetModelMatrix() = glm::translate(m_Mesh.GetModelMatrix(), m_Position);
		  

		m_Texture.Bind();
		m_Mesh.Render(ShaderManager::Self()->GetShader(m_Shader));
		m_Texture.Unbind();
	}
};