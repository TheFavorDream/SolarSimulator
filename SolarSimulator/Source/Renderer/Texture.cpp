#include "Texture.h"

namespace Simulator
{
	Texture::~Texture()
	{
	}
	uint32 Texture::GetTextureLimit()
	{
		int Data = 0;
		glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &Data);
		return Data;
	}

	GLenum Texture::GetColorChannel(uint32 pChannels)
	{
		switch (pChannels)
		{
		case 1: return GL_R;
		case 2: return GL_RG;
		case 3: return GL_RGB;
		case 4: return GL_RGBA;
		}
		return GL_INVALID_ENUM;
	}

//=========2D texture=================================


	Texture2D::Texture2D(std::string pPath)
	{
		CreateTexture(pPath);
	}

	Texture2D::~Texture2D()
	{
		FreeTexture();
	}

	int Texture2D::CreateTexture(std::string pFilePath, bool pKeepCache)
	{
		stbi_set_flip_vertically_on_load(true);
		m_Data = stbi_load(pFilePath.c_str(), &m_Width, &m_Height, &m_Channels, NULL);

		if (m_Data == NULL)
		{
			Log::GetSelf()->SetError("Unable to Load Texture from %s", pFilePath);
			return 1;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLenum Format = Texture::GetColorChannel(m_Channels);
		glTexImage2D(GL_TEXTURE_2D, 0, Format, m_Width, m_Height, 0, Format, GL_UNSIGNED_BYTE, (void*)m_Data);

		if (!pKeepCache)
		{
			stbi_image_free(m_Data);
			m_Data = NULL;
		}

		return 0;
	}

	int Texture2D::CreateTexture(unsigned char * pData, uint32 pWidth, uint32 pHegith, uint32 pChannels)
	{
		if (pData == NULL)
		{
			Log::GetSelf()->SetError("No Data was Passed to CreateTexture()");
			return 1;
		}
		m_Data = pData;
		m_Width = pWidth;
		m_Height = pHegith;
		m_Channels = pChannels;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		GLenum Format = Texture::GetColorChannel(m_Channels);
		glTexImage2D(GL_TEXTURE_2D, 0, Format, m_Width, m_Height, 0, Format, GL_UNSIGNED_BYTE, (void*)m_Data);

		return 0;
	}

	int Texture2D::FreeTexture()
	{
		Unbind();
		glDeleteTextures(1, &m_TextureID);
		stbi_image_free(m_Data);
		Log::GetSelf()->SetInfo("Destructor of Texture Class Called. ID:%i", m_TextureID);
		return 0;
	}

	void Texture2D::Bind(uint32 Slot) const
	{
		if (Slot > Texture::GetTextureLimit())
		{
			Log::GetSelf()->SetWarning("Texture Bind Limit Exceeded: %i", Texture::GetTextureLimit());
			return;
		}
		m_CurrentSlot = Slot;
		glActiveTexture(GL_TEXTURE0+Slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture2D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};