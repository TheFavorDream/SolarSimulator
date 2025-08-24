#include "SkyBox.h"

Simulator::SkyBox::SkyBox(std::string pTexturePath)
{
	
}
Simulator::SkyBox::~SkyBox()
{
	FreeSkyBox();
}


void Simulator::SkyBox::CreateSkyBox(std::string pSubPath, const std::vector<std::string>& pFiles)
{
	m_Shader = ShaderManager::Self()->CreateNewShader(m_VertexShader, m_FragmentShader);
	m_CubeMap.CreateTexture(pSubPath, pFiles, false);
	ShaderManager::Self()->GetShader(m_Shader).SetUniformInt1("skybox", 0);
	m_Cube.SetUp(m_Vertices, std::vector<uint16>());
	m_Cube.GetModelMatrix() = glm::mat4(1.0f);
}

void Simulator::SkyBox::FreeSkyBox()
{

	m_CubeMap.FreeTexture();
}

void Simulator::SkyBox::RenderSkyBox()
{
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);

	m_CubeMap.Bind(0);
	m_Cube.Render(ShaderManager::Self()->GetShader(m_Shader));

	m_CubeMap.Unbind();
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

}
