#include "Uranus.h"


namespace Simulator
{
	Uranus::Uranus(std::string pModelPath, uint32 pShader)
	{
		m_Mesh.LoadMesh(pModelPath);

		m_Shader = pShader;
		m_Texture.CreateTexture(std::string(ASSETS_PARENT_DIR) + "Uranus.jpg", GL_LINEAR, GL_LINEAR, false);
		m_Position = glm::vec3(0.0f, 0.0f, 100.0f);
	}

	Uranus::~Uranus()
	{
	}

	void Uranus::Render()
	{
		float Time = (float)glfwGetTime()*0.03f;
		static float MoveX = rand(), MoveZ = MoveX;
		m_Position = glm::vec3(sin(MoveX + Time)*Radius, 0.0f, cos(MoveZ + Time)*Radius);

		m_Mesh.GetModelMatrix() = glm::mat4(1.0f);
		m_Mesh.GetModelMatrix() = glm::translate(m_Mesh.GetModelMatrix(), m_Position);
		m_Mesh.GetModelMatrix() = glm::rotate(m_Mesh.GetModelMatrix(), (float)glfwGetTime()*1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		m_Mesh.GetModelMatrix() = glm::scale(m_Mesh.GetModelMatrix(), glm::vec3(1.5f));


		m_Texture.Bind();
		m_Mesh.Render(ShaderManager::Self()->GetShader(m_Shader));
		m_Texture.Unbind();
	}
};