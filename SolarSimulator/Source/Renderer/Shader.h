/*

	Created by Pooya Alizadeg (The Voltage)
	Purpose:
		Shader Implemention class

*/
#pragma once
#include "../Core.h"
#include "../LogSys/Log.h"
#include "../../3rdParty/glew/include/GL/glew.h"
#include <unordered_map>
#include <vector>
#include <string>
#include <fstream>
#include "../3rdParty/glm/mat4x4.hpp"
#include "../3rdParty/glm/gtc/type_ptr.hpp"

namespace Simulator
{
	class Shader
	{
	public:

		Shader() = default;
		Shader(std::string pShaderPath);
		Shader(const std::string& pVertexSource, const std::string& pFragmentSource);
		~Shader();

		int CreateShader(std::string pShaderPath);
		int CreateShader(const std::string& pVertexSource, const std::string& pFragmentSource);
		int DeleteShader();

		void Bind() const;
		void Unbind() const;

		void SetUniformFloat1(const char* pName, float pValue) const;
		void SetUniformFloat2(const char* pName, float pValue1, float pValue2) const;
		void SetUniformFloat3(const char* pName, float pValue1, float pValue2, float pValue3) const;

		void SetUniformInt1(const char* pName, int32 pValue) const;
		void SetUniformInt2(const char* pName, int32 pValue1, int32 pValue2) const;
		void SetUniformInt3(const char* pName, int32 pValue1, int32 pValue2, int32 pValue3) const;

		void SetUniformMat4(const char* pName, glm::mat4& pValue) const;

		inline const std::string& GetShaderPath() { return m_ShaderPath; }

	private:
		int32 GetUniformLocation(const char* pName) const;

		std::string ReadShaderFile(const std::string& pShaderPath);
		std::vector<std::string> FilterSource(const std::string& pShaderSource);
		int Preprocess(const std::vector<std::string>& pShaderContent);
		int CompileShader(GLenum pType, const std::string& pSource);
		int CreateProgram();

		GLenum GetShaderEnum(std::string ShaderName);

	private:
		uint32 m_ProgramID = 0;
		std::string m_ShaderPath;
		std::unordered_map<GLenum, std::string> m_ShadersSources;
		mutable std::unordered_map<const char*, int32> m_UniformLookUp; //for faster uniform access

	};
};
