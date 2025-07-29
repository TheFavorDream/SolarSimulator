#include "Mesh.h"


namespace Simulator
{
	Mesh::Mesh(const std::vector<Vertex>& pVertices)
	{
		SetUp(pVertices, std::vector<uint32>());
	}

	Mesh::Mesh(const std::vector<Vertex>& pVertices, const std::vector<uint32>& pIndices)
	{
		SetUp(pVertices, pIndices);
	}

	Mesh::~Mesh()
	{
		Free();
	}

	void Mesh::Render(const Shader& pShader)
	{
		pShader.Bind();

		m_VAO.Bind();
		glDrawElements(GL_TRIANGLES, m_EBO.GetCount(), GL_UNSIGNED_INT, 0);
		m_VAO.Unbind();
	}

	void Mesh::SetUp(const std::vector<Vertex>& pVertices, const std::vector<uint32>& pIndices)
	{
		m_Vertices = pVertices;
		m_Indices = pIndices;

		m_VAO.CreateVertexArray();
		m_VAO.Bind();

		m_VBO.InitBuffer(pVertices);
		m_EBO.InitBuffer(pIndices);

		m_VAO.AddLayout(GL_FLOAT, 3, GL_FALSE);
		m_VAO.AddLayout(GL_FLOAT, 3, GL_FALSE);
		m_VAO.AddLayout(GL_FLOAT, 2, GL_FALSE);
		m_VAO.LoadLayout(m_VBO, m_EBO);
		m_VAO.Unbind();
	}
	void Mesh::Free()
	{
		m_Vertices.clear();
		m_Indices.clear();
	}
};