#pragma once

#include "../Core.h"
#include "../../3rdParty/glew/include/GL/glew.h"
#include "Texture.h"
#include "../LogSys/Log.h"

namespace Simulator
{

	class FrameBuffer
	{
	public:

		FrameBuffer();
		~FrameBuffer();


		int CreateFrameBuffer(uint32 pWidth, uint32 pHeight, uint32 pColorBuffer=1);
		int DestroyFrameBuffer();

		void ClearBuffer();
		void ResizeColorBuffer(uint32 pWidth, uint32 pHeight);

		void BindColorBuffer(uint32 pAttachment, uint32 pSlot=0);

		void Bind();
		void Unbind();

	private:
		uint32 m_FBO; //Frame  Buffer
		uint32 m_RBO; //Render Buffer
		uint32 m_Width, m_Height;

		std::vector<Texture2D> m_ColorBuffers;
	public:
		static std::vector<FrameBuffer*> s_FrameBuffers;
	};

};
