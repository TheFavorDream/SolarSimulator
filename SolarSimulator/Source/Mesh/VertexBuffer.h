#pragma once
#include "../Core.h"
#include "../../3rdParty/glew/include/GL/glew.h"
#include "../../3rdParty/glm/vec3.hpp"
#include "../../3rdParty/glm/vec2.hpp"

#include <vector>

namespace Simulator
{


	struct Vertex
	{
		glm::vec3 Postion;
		glm::vec3 Normal;
		glm::vec2 TexCoords;
	};

	class VertexBuffer
	{
	public:

		 VertexBuffer(const std::vector<Vertex>& pVertices);
		 VertexBuffer() = default;
		 VertexBuffer(VertexBuffer&& Other);
		 ~VertexBuffer();


		void InitBuffer(const std::vector<Vertex>& pVertices);
		void FreeBuffer();

		void Bind()   const;
		void Unbind() const;

		inline uint32 GetID() { return m_BufferID; }
		inline uint32 GetVertexNumbers() { return m_Vertices; }
	private:
		uint32 m_BufferID = 0;
		uint32 m_Vertices = 0;
	};

};