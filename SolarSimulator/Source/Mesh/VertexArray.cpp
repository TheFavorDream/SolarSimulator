#include "VertexArray.h"


namespace Simulator
{

	VertexArray::VertexArray()
	{
	}

	VertexArray::VertexArray(VertexArray && Other)
	{
		m_ArrayID = Other.m_ArrayID;
		m_Layouts = Other.m_Layouts;
		Other.m_ArrayID = 0;
	}

	VertexArray::~VertexArray()
	{
		DeleteVertexArray();
	}

	void VertexArray::CreateVertexArray()
	{
		glGenVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::DeleteVertexArray()
	{
		Unbind();
		glDeleteVertexArrays(1, &m_ArrayID);
	}

	void VertexArray::Bind() const
	{
		glBindVertexArray(m_ArrayID);
	}

	void VertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddLayout(GLenum pType, uint32 pCount, GLboolean pNormalized)
	{
		m_Layouts.push_back({pCount, pType, pNormalized});
		m_Stride += (pCount*Layout::GetSize(pType));
	}

	void VertexArray::LoadLayout(const VertexBuffer & pVBO, const ElementBuffer & pEBO)
	{
		Bind();
		pVBO.Bind();
		pEBO.Bind();
		uint32 Offset = 0;
		for (int i = 0; i < m_Layouts.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, m_Layouts[i].Count, m_Layouts[i].Type, m_Layouts[i].Normalized, m_Stride, (void*)Offset);
			Offset += m_Layouts[i].Count * Layout::GetSize(m_Layouts[i].Type);
		}
	}

};