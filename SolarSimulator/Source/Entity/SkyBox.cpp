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
	m_Shader.CreateShader(m_VertexShader, m_FragmentShader);
	m_CubeMap.CreateTexture(pSubPath, pFiles, false);
	m_Shader.SetUniformInt1("skybox", 0);
	m_Cube.SetUp(m_Vertices, std::vector<uint16>());
	m_Cube.GetMatrix() = glm::mat4(1.0f);
}

void Simulator::SkyBox::FreeSkyBox()
{
	m_Shader.DeleteShader();
	m_CubeMap.FreeTexture();
}

void Simulator::SkyBox::RenderSkyBox(Camera& pCamera)
{
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	m_Shader.Bind();
	m_CubeMap.Bind(0);
	m_Cube.Render(m_Shader, pCamera);
	m_Shader.Unbind();
	m_CubeMap.Unbind();
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

}
