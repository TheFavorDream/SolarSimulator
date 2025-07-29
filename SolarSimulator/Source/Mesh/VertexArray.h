#pragma once
#include "../Core.h"
#include "../../3rdParty/glew/include/GL/glew.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include <vector>

namespace Simulator
{

	struct Layout
	{
		uint32 Count;
		GLenum Type;
		GLboolean Normalized;

		static uint32 GetSize(GLenum pType)
		{
			switch (pType)
			{
			case GL_FLOAT:
				return sizeof(float);
			case GL_INT:
				return sizeof(int);
			case GL_BYTE:
				return sizeof(char);
			default:
				return 0;
			}
		}
	};

	class VertexArray
	{
	public:
		 VertexArray();
		 VertexArray(VertexArray&& Other);
		~VertexArray();

		void CreateVertexArray();
		void DeleteVertexArray();

		void Bind() const;
		void Unbind() const;

		void AddLayout(GLenum pType, uint32 pCount, GLboolean pNormalized);
		void LoadLayout(const VertexBuffer& pVBO, const ElementBuffer&  pEBO);
	
	private:
		uint32 m_ArrayID = 0;
		std::vector<Layout> m_Layouts;
		uint32 m_Stride = 0;
	};
};