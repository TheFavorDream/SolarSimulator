#include "ElementBuffer.h"


namespace Simulator
{
	ElementBuffer::ElementBuffer(const std::vector<uint16>& pIndices)
	{
		InitBuffer(pIndices);
	}

	ElementBuffer::ElementBuffer(ElementBuffer && Other)
	{
		m_BufferID = Other.m_BufferID;
		m_Count = Other.m_Count;
		Other.m_BufferID = 0;
	}

	ElementBuffer::~ElementBuffer()
	{
		FreeBuffer();
	}

	void ElementBuffer::operator=(ElementBuffer && Other) noexcept
	{
		m_BufferID = Other.m_BufferID;
		m_Count = Other.m_Count;
		Other.m_BufferID = 0;
	}

	void ElementBuffer::InitBuffer(const std::vector<uint16>& pIndices)
	{
		glGenBuffers(1, &m_BufferID);
		m_Count = pIndices.size();
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count*sizeof(uint16), &pIndices[0], GL_STATIC_DRAW);
	}

	void ElementBuffer::FreeBuffer()
	{
		Unbind();
		glDeleteBuffers(1, &m_BufferID);
	}

	void ElementBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
	}

	void ElementBuffer::Unbind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
};