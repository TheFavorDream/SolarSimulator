#include "../Core.h"
#include "../../3rdParty/glew/include/GL/glew.h"
#include <vector>

namespace Simulator
{
	class ElementBuffer
	{
	public:

		ElementBuffer() = default;
		ElementBuffer(const std::vector<uint32>& pIndices);
		ElementBuffer(ElementBuffer&& Other);
		~ElementBuffer();

		void InitBuffer(const std::vector<uint32>& pIndices);
		void FreeBuffer();

		void Bind() const;
		void Unbind() const;

		inline uint32 GetID() { return m_BufferID; }
		inline uint32 GetCount() { return m_Count; }

	private:
		uint32 m_BufferID = 0;
		uint32 m_Count = 0;
	};
};