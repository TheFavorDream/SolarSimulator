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





	Texture2D::Texture2D(std::string pPath, GLenum pMin, GLenum pMag)
	{
		CreateTexture(pPath, pMin, pMag);
	}

	Texture2D::Texture2D(Texture2D && Other)
	{
		m_TextureID = Other.m_TextureID;
		m_Width = Other.m_Width;
		m_Height = Other.m_Height;

		Other.m_TextureID = 0;
	}

	Texture2D::~Texture2D()
	{
		FreeTexture();
	}

	int Texture2D::CreateTexture(std::string pFilePath, GLenum pMin, GLenum pMag, bool pFlipVerticaly, bool pKeepCache)
	{
		stbi_set_flip_vertically_on_load(pFlipVerticaly);
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

	int Texture2D::CreateTexture(uint8 * pData, uint32 pWidth, uint32 pHeight, GLenum pFormat)
	{

		m_Width = pWidth;
		m_Height = pHeight;


		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0,  pFormat, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)pData);

		return 0;
	}

	int Texture2D::CreateTextureFromMemory(uint8 * pData, uint32 pLength, GLenum pMin, GLenum pMag, bool pFlipVerticaly)
	{
		stbi_set_flip_vertically_on_load(pFlipVerticaly);
		m_Data = stbi_load_from_memory(pData, pLength , &m_Width, &m_Height, &m_Channels, NULL);

		if (m_Data == NULL)
		{
			Log::GetSelf()->SetError("Unable to Load Texture from memory");
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

		
		stbi_image_free(m_Data);
		m_Data = NULL;
		
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

//=================================================
	TextureCube::TextureCube(TextureCube && Other)
	{
	}
	TextureCube::~TextureCube()
	{
		FreeTexture();
	}

	int TextureCube::CreateTexture(std::string pFilePath, GLenum pMin, GLenum pMag, bool pFlipVerticaly, bool pKeepCache)
	{
		stbi_set_flip_vertically_on_load(pFlipVerticaly);
		m_Data = stbi_load(pFilePath.c_str(), &m_Width, &m_Height, &m_Channels, NULL);

		if (m_Data == NULL)
		{
			Log::GetSelf()->SetError("Unable to Load Texture from %s", pFilePath);
			return 1;
		}

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
		GLenum Format = Texture::GetColorChannel(m_Channels);

		for (int i = 0; i < 6; i++)
		{
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X+i, 0, Format, m_Width, m_Height, 0, Format, GL_UNSIGNED_BYTE, (void*)m_Data);
		}



		if (!pKeepCache)
		{
			stbi_image_free(m_Data);
			m_Data = NULL;
		}

		return 0;
	}
	int TextureCube::CreateTexture(std::string pDirectoryPath, const std::vector<std::string>& pFiles, bool pKeepCache)
	{

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
		for (int i = 0; i < 6; i++)
		{
			stbi_set_flip_vertically_on_load(true);
			m_Data = stbi_load((pDirectoryPath + pFiles[i]).c_str(), &m_Width, &m_Height, &m_Channels, NULL);

			if (m_Data == NULL)
			{
				Log::GetSelf()->SetError("Unable to Load Texture from %s", pFiles[i]);
				continue;
			}


			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			GLenum Format = Texture::GetColorChannel(m_Channels);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, Format, m_Width, m_Height, 0, Format, GL_UNSIGNED_BYTE, (void*)m_Data);
			stbi_image_free(m_Data);
		}
		return 0;
	}

	int TextureCube::FreeTexture()
	{
		Unbind();
		glDeleteTextures(1, &m_TextureID);
		return 0;
	}

	void TextureCube::Bind(uint32 Slot) const
	{
		if (Slot > Texture::GetTextureLimit())
		{
			Log::GetSelf()->SetWarning("Texture Bind Limit Exceeded: %i", Texture::GetTextureLimit());
			return;
		}
		m_CurrentSlot = Slot;
		glActiveTexture(GL_TEXTURE0 + Slot);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID);
	}
	void TextureCube::Unbind() const
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}
};