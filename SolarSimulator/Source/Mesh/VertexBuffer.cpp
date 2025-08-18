#include "VertexBuffer.h"


namespace Simulator
{
	VertexBuffer::VertexBuffer(const std::vector<Vertex>& pVertices)
	{
		InitBuffer(pVertices);
	}

	VertexBuffer::VertexBuffer(VertexBuffer && Other)
	{
		m_BufferID = Other.m_BufferID;
		m_Vertices = Other.m_Vertices;
		Other.m_BufferID = 0;
		Other.m_Vertices = 0;
	}

	VertexBuffer::~VertexBuffer()
	{
		FreeBuffer();
	}

	void VertexBuffer::operator=(VertexBuffer && Other) noexcept
	{
		m_BufferID = Other.m_BufferID;
		m_Vertices = Other.m_Vertices;
		Other.m_BufferID = 0;
		Other.m_Vertices = 0;
	}

	void VertexBuffer::InitBuffer(const std::vector<Vertex>& pVertices)
	{
		glGenBuffers(1, &m_BufferID);
		Bind();
		m_Vertices = pVertices.size();
		glBufferData(GL_ARRAY_BUFFER, m_Vertices*sizeof(Vertex), &pVertices[0], GL_STATIC_DRAW);
	}

	void VertexBuffer::FreeBuffer()
	{
		Unbind();
		glDeleteBuffers(1, &m_BufferID);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferID);
	}
	void VertexBuffer::Unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

};