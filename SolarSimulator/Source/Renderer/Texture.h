/*

	Created by Pooya Alizadeh (The Voltage)
	Purpose:
		Takes care of Texture Loading.

*/

#pragma once
#include "../Core.h"
#include "../LogSys/Log.h"
#include "../../3rdParty/glew/include/GL/glew.h"
#include "../../3rdParty/stb_image/stb_image.h"
#include <string>
#include <vector>

namespace Simulator
{
	class Texture
	{
	public:

		Texture() = default;

		virtual ~Texture() ;


		virtual int CreateTexture(std::string pFilePath, GLenum pMin = GL_LINEAR, GLenum pMag = GL_LINEAR, bool pFlipVerticaly=true, bool pKeepCache=false) = 0;
		virtual int FreeTexture() = 0;

		virtual void Bind(uint32 Slot=0) const = 0;
		virtual void Unbind() const = 0;

		inline uint32 GetWidth()  { return m_Width; }
		inline uint32 GetHeight() { return m_Height; }
		inline uint32 GetTexture() { return m_TextureID; }

	public:
		static uint32 GetTextureLimit();
		static GLenum GetColorChannel(uint32 pChannels);
	protected:
		int32 m_Width, m_Height, m_Channels;
		uint32 m_TextureID = 0;
		unsigned char* m_Data = NULL;
		mutable uint32 m_CurrentSlot;
	};


	class Texture2D : public Texture
	{
	public:

		 Texture2D() = default;
		 Texture2D(std::string pPath, GLenum pMin = GL_LINEAR, GLenum pMag= GL_LINEAR);
		 Texture2D(Texture2D&& Other);
		~Texture2D();

		int CreateTexture(std::string pFilePath, GLenum pMin = GL_LINEAR, GLenum pMag = GL_LINEAR, bool pFlipVerticaly=true, bool pKeepCache = false) override;
		int CreateTexture(uint8* pData, uint32 pWidth, uint32 pHeight, GLenum pFormat = GL_RGB);
		int CreateTextureFromMemory(uint8* pData, uint32 pLength, GLenum pMin = GL_LINEAR, GLenum pMag = GL_LINEAR, bool pFlipVerticaly = true);
		int FreeTexture() override;

		void Bind(uint32 Slot = 0) const override;
		void Unbind() const override;

	private:
		std::string m_Path;
	};



	class TextureCube : public Texture
	{
	public:
		 TextureCube() = default;
		 TextureCube(TextureCube&& Other);
		~TextureCube();

		//This will use the same single texture to fill all 6 sides:
		int CreateTexture(std::string pFilePath, GLenum pMin = GL_LINEAR, GLenum pMag = GL_LINEAR, bool pFlipVerticaly = true, bool pKeepCache = false) override;

		// Gets 6 textures and makes a cube map
		int CreateTexture(std::string pDirectoryPath, const std::vector<std::string>& pFiles, bool pKeepCache=false);

		int FreeTexture() override;

		void Bind(uint32 Slot = 0) const override;
		void Unbind() const override;

	private:
	};
};