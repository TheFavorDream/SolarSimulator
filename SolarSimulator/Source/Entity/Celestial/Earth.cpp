#include "Earth.h"


namespace Simulator
{
	Earth::Earth(std::string pModelPath, uint32 pShader)
	{
		m_Mesh.LoadMesh(pModelPath);

		m_Shader = pShader;

		//Loading Textures
		m_EarthTexture.CreateTexture(std::string(ASSETS_PARENT_DIR)+"Earth.jpg", GL_LINEAR, GL_LINEAR, false);
		m_EarthClouds.CreateTexture(std::string(ASSETS_PARENT_DIR) + "EarthClouds.jpg", GL_LINEAR, GL_LINEAR, false);
		m_EarthSpecMap.CreateTexture(std::string(ASSETS_PARENT_DIR) +  "EarthSpec.jpg", GL_LINEAR, GL_LINEAR, false);
		m_EarthNight.CreateTexture(std::string(ASSETS_PARENT_DIR) + "EarthNight.jpg", GL_LINEAR, GL_LINEAR, false);



		m_Properties.Position = glm::vec3(30.0f, 0.0f, 60.0f);
		m_Properties.Volacity = glm::vec3(0.0f,  0.0f, -0.001f);

		ShaderManager::Self()->GetShader(m_Shader).SetUniformInt1("Texture", 0);
		ShaderManager::Self()->GetShader(m_Shader).SetUniformInt1("TextureCloud", 1);
		ShaderManager::Self()->GetShader(m_Shader).SetUniformInt1("TextureSpec", 2);
		ShaderManager::Self()->GetShader(m_Shader).SetUniformInt1("TextureNight", 3);
	}

	Earth::~Earth()
	{
	}

	void Earth::Render()
	{


		m_Mesh.GetModelMatrix() = glm::mat4(1.0f);
		m_Mesh.GetModelMatrix() = glm::translate(m_Mesh.GetModelMatrix(), m_Properties.Position);
		m_Mesh.GetModelMatrix() = glm::rotate(m_Mesh.GetModelMatrix(), (float)glfwGetTime()*1.0f, glm::vec3(0.0f, 1.0f, 0.0f));



		m_EarthTexture.Bind(0);
		m_EarthClouds.Bind(1);
		m_EarthSpecMap.Bind(2);
		m_EarthNight.Bind(3);

		m_Mesh.Render(ShaderManager::Self()->GetShader(m_Shader));
		m_EarthTexture.Unbind();
		m_EarthClouds.Unbind();
		m_EarthSpecMap.Unbind();
		m_EarthNight.Unbind();
	}
};