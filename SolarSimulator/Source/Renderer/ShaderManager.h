#pragma once


#include "../Core.h"
#include "../LogSys/Log.h"
#include "Shader.h"

#include <unordered_map>
#include <string>

namespace Simulator
{

	class ShaderManager
	{
	public:

		 ShaderManager();
		~ShaderManager();


		//Creates a new shader and return a access key:
		uint32 CreateNewShaderFromPath(std::string pShaderPath);
		uint32 CreateNewShader(const std::string& pVertexShader, const std::string& pFragmentShader);

		//Deletes an existing shader by its key:
		uint32 DeleteShader(uint32 pKey);

		void BindShader(uint32 pKey);
		void UnbindCurrent();


		Shader& GetShader(uint32 pKey);

		//Uniform Setters:

		/*
		
			Broad Casting:
			It is functionality whitch lets you set a uniform through all the existing shaders.
		*/

		void BroadCastUniform1F(const char* pUniformName, float pValue) noexcept;
		void BroadCastUniform2F(const char* pUniformName, float pValue1, float pValue2, float pValue3) noexcept;
		void BroadCastUniform3F(const char* pUniformName, float pValue1, float pValue2, float pValue3) noexcept;
		void BroadCastUniform3F(const char* pUniformName, glm::vec3 pValues) noexcept;

		
		void BroadCastUniform1I(const char* pUniformName, int32  pValue) noexcept;
		void BroadCastUniform2I(const char* pUniformName, int32  pValue1, int32 pValue2, int32 pValue3) noexcept;
		void BroadCastUniform3I(const char* pUniformName, int32  pValue1, int32 pValue2, int32 pValue3) noexcept;
	
		void BroadCastUniformMat4(const char* pUniformName, glm::mat4& pValue);

		inline uint32 GetShaderNums() { return m_Shaders.size(); }
		inline const Shader& operator[](uint32 pKey) { return m_Shaders[pKey]; }

	private:
		bool DoesShaderExist(uint32 pKey);
	public:
		static ShaderManager* Self();
	
	private:
		std::unordered_map<uint32, Shader> m_Shaders;
		Shader* m_CurrentShader;
	private:
		static ShaderManager* s_Self;
	};

};