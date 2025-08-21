#include "Mesh.h"


namespace Simulator
{
	Mesh::Mesh(const std::vector<Vertex>& pVertices)
	{
		SetUp(pVertices, std::vector<uint16>());
	}

	Mesh::Mesh(const std::vector<Vertex>& pVertices, const std::vector<uint16>& pIndices, int32 pMaterialIndex)
		:m_MaterialIndex(pMaterialIndex)
	{
		SetUp(pVertices, pIndices);
	}

	Mesh::Mesh(Mesh&& Other) noexcept
	{
		m_Vertices = Other.m_Vertices;
		m_Indices = Other.m_Indices;
		m_MaterialIndex = Other.m_MaterialIndex;
			
		m_Model = Other.m_Model;
		m_VBO = std::move(Other.m_VBO);
		m_VAO = std::move(Other.m_VAO);
		m_EBO = std::move(Other.m_EBO);
		
	}

	Mesh::~Mesh()
	{
		Free();
	}

	void Mesh::Render(const Shader& pShader, Camera& pCamera, glm::mat4& pTransform)
	{
		pShader.Bind();


		pShader.SetUniformMat4("Model", m_Model*pTransform);
		pShader.SetUniformMat4("View", pCamera.GetView());
		pShader.SetUniformMat4("Projection", pCamera.GetProjection());

		m_VAO.Bind();
		if (m_EBO.GetCount() != 0)
			glDrawElements(GL_TRIANGLES, m_EBO.GetCount(), GL_UNSIGNED_SHORT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, m_VBO.GetVertexNumbers());
		m_VAO.Unbind();
	}

	void Mesh::SetUp(const std::vector<Vertex>& pVertices, const std::vector<uint16>& pIndices)
	{
		m_Vertices = pVertices;
		m_Indices  = pIndices;

		m_VAO.CreateVertexArray();
		m_VAO.Bind();

		m_VBO.InitBuffer(pVertices);
		m_EBO.InitBuffer(pIndices);

		m_VAO.AddLayout(GL_FLOAT, 3, GL_FALSE);
		m_VAO.AddLayout(GL_FLOAT, 3, GL_FALSE);
		m_VAO.AddLayout(GL_FLOAT, 2, GL_FALSE);
		m_VAO.LoadLayout(m_VBO, m_EBO);
		m_VAO.Unbind();

		m_Vertices.clear();
		m_Indices.clear();
	}
	void Mesh::Free()
	{
		m_Vertices.clear();
		m_Indices.clear();
	}
};