#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"

#include <vector>

namespace Simulator
{
	class Mesh
	{
	public:

		Mesh() = default;
		Mesh(const std::vector<Vertex>& pVertices);
		Mesh(const std::vector<Vertex>& pVertices, const std::vector<uint32>& pIndices);
		~Mesh();

		void Render();
		void SetUp(const std::vector<Vertex>& pVertices, const std::vector<uint32>& pIndices);
		void Free();

	private:
		VertexArray  m_VAO;
		VertexBuffer m_VBO;
		ElementBuffer m_EBO;

		std::vector<Vertex> m_Vertices;
		std::vector<uint32> m_Indices;
	};
};