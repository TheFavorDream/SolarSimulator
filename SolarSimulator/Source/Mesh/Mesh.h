#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "../Renderer/Shader.h"
#include "../Camera/Camera.h"
#include "../Renderer/Texture.h"

#include <vector>

namespace Simulator
{
	class Mesh
	{
	public:

		Mesh() = default;
		Mesh(const std::vector<Vertex>& pVertices);
		Mesh(const std::vector<Vertex>& pVertices, const std::vector<uint16>& pIndices, int32 pMaterialIndex);
		Mesh(Mesh&& Other) noexcept; //Move Constructor
		~Mesh();

		inline glm::mat4& GetMatrix() { return m_Model; }
		inline int32 GetMaterialIndex() { return m_MaterialIndex; }

		void Render(const Shader& pShader, Camera& pCamera, glm::mat4& pTransform=glm::mat4(1.0f));
		void SetUp(const std::vector<Vertex>& pVertices, const std::vector<uint16>& pIndices);
		void Free();

	private:
		VertexArray  m_VAO;
		VertexBuffer m_VBO;
		ElementBuffer m_EBO;

		glm::mat4 m_Model = glm::mat4(1.0f);

		std::vector<Vertex> m_Vertices;
		std::vector<uint16> m_Indices;
		int32 m_MaterialIndex = 0;
	};
};