#include "Jupiter.h"


namespace Simulator
{
	Jupiter::Jupiter(std::string pModelPath, uint32 pShader)
	{
		m_Mesh.LoadMesh(pModelPath);
		m_Shader = pShader;

		m_Position = glm::vec3(0.0f, 0.0f, 30.0f);
		m_Texture.CreateTexture(std::string(ASSETS_PARENT_DIR) + "Jupiter.jpg", GL_LINEAR, GL_LINEAR, false);
	}

	Jupiter::~Jupiter()
	{
	}

	void Jupiter::Render()
	{
		float Time = (float)glfwGetTime() * 0.05f;
		static float MoveX = rand(), MoveZ = MoveX;
		m_Position = glm::vec3(sin(MoveX + Time)*Radius, 0.0f, cos(MoveZ + Time)*Radius);

		m_Mesh.GetModelMatrix() = glm::mat4(1.0f);
		m_Mesh.GetModelMatrix() = glm::translate(m_Mesh.GetModelMatrix(), m_Position);
		m_Mesh.GetModelMatrix() = glm::rotate(m_Mesh.GetModelMatrix(), (float)glfwGetTime()*1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		m_Mesh.GetModelMatrix() = glm::scale(m_Mesh.GetModelMatrix(), glm::vec3(4.0f));


		m_Texture.Bind();
		m_Mesh.Render(ShaderManager::Self()->GetShader(m_Shader));
		m_Texture.Unbind();
	}
};