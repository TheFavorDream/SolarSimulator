#include "FrameBuffer.h"


namespace Simulator
{
	
	std::vector<FrameBuffer*> FrameBuffer::s_FrameBuffers;

	FrameBuffer::FrameBuffer()
	{
		s_FrameBuffers.push_back(this);
	}

	FrameBuffer::~FrameBuffer()
	{
		DestroyFrameBuffer();
	}


	int FrameBuffer::CreateFrameBuffer(uint32 pWidth, uint32 pHeight, uint32 pColorBuffer)
	{
		glGenFramebuffers(1, &m_FBO);
		Bind();


		//Creating and attaching Color Buffer:
		std::vector<GLenum> attachments;
		for (int i = 0; i < pColorBuffer; i++)
		{
			Texture2D ColorBuffer;
			ColorBuffer.CreateTexture(NULL, pWidth, pHeight, GL_RGBA16F);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, ColorBuffer.GetTexture(), 0);
			m_ColorBuffers.emplace_back(std::move(ColorBuffer));
			attachments.emplace_back(GL_COLOR_ATTACHMENT0+i);
		}
		glDrawBuffers(pColorBuffer, &attachments[0]);


		//Creating Depth & Stencil Buffer:
		glGenRenderbuffers(1, &m_RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, pWidth, pHeight);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);



		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		{
			Log::GetSelf()->SetError("Failed to Create FrameBuffer. ID:%i", m_FBO);
			return 1;
		}

		return 0;
	}

	int FrameBuffer::DestroyFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FBO);
		glDeleteRenderbuffers(1, &m_RBO);

		for (int i = 0; i < m_ColorBuffers.size(); i++)
		{
			m_ColorBuffers[i].Unbind();
			m_ColorBuffers[i].FreeTexture();
		}
		m_ColorBuffers.clear();

		return 0;
	}

	void FrameBuffer::ClearBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void FrameBuffer::ResizeColorBuffer(uint32 pWidth, uint32 pHeight)
	{
		uint32 ColorBuffers = m_ColorBuffers.size();
		DestroyFrameBuffer();
		CreateFrameBuffer(pWidth, pHeight, ColorBuffers);
	}

	void FrameBuffer::BindColorBuffer(uint32 pAttachment, uint32 pSlot)
	{
		if (pAttachment >= m_ColorBuffers.size())
		{
			Log::GetSelf()->SetWarning("Trying to access out of bound texture attachments");
			return;
		}

		m_ColorBuffers[pAttachment].Bind(pSlot);
	}


	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
	}

	void FrameBuffer::Unbind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0); //Binding the defualt FrameBuffer
	}

};