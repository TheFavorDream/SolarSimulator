#include "ShaderManager.h"
#include "ShaderManager.h"
#include "ShaderManager.h"


namespace Simulator
{


	ShaderManager* ShaderManager::s_Self = NULL;



	ShaderManager* ShaderManager::Self()
	{
		if (s_Self == NULL)
		{
			s_Self = new ShaderManager();
		}
		return s_Self;
	}

//==================================================================

	ShaderManager::ShaderManager()
	{
		Log::GetSelf()->SetInfo("Shader Manager Started");
	}

	ShaderManager::~ShaderManager()
	{
		Log::GetSelf()->SetInfo("Shader Manager Shutdown");

		for (auto &i : m_Shaders)
		{
			i.second.DeleteShader();
		}

	}

//==========================Shader Operations===========================================

	uint32 ShaderManager::CreateNewShader(std::string pShaderPath)
	{
		uint32 Key = m_Shaders.size();
		m_Shaders[Key].CreateShader(pShaderPath);
		return Key;
	}

	uint32 ShaderManager::CreateNewShader(const std::string & pVertexShader, const std::string & pFragmentShader)
	{
		uint32 Key = m_Shaders.size();
		m_Shaders[Key].CreateShader(pVertexShader, pFragmentShader);
		return Key;
	}

	uint32 ShaderManager::DeleteShader(uint32 pKey)
	{
		if (!DoesShaderExist(pKey))
		{
			Log::GetSelf()->SetError("Attempting to delete an shader that does not exist!");
			return pKey;
		}

		m_Shaders.erase(m_Shaders.find(pKey));
		return 0;
	}

	void ShaderManager::BindShader(uint32 pKey)
	{
		if (!DoesShaderExist(pKey))
		{
			Log::GetSelf()->SetError("Invalid shader key");
			return;
		}
		m_CurrentShader = &m_Shaders[pKey];
		m_Shaders[pKey].Bind();
	}

	void ShaderManager::UnbindCurrent()
	{
		if (m_CurrentShader == NULL)
		{
			Log::GetSelf()->SetWarning("No Shader were binded");
			return;
		}
		m_CurrentShader->Unbind();
	}

	Shader & ShaderManager::GetShader(uint32 pKey)
	{
		if (!DoesShaderExist(pKey))
		{
			Log::GetSelf()->SetError("shader not found");
			assert(false);
		}
		return m_Shaders[pKey];
	}

	bool ShaderManager::DoesShaderExist(uint32 pKey)
	{
		if (m_Shaders.find(pKey) == m_Shaders.end())
			return false;
		return true;
	}

//==============================Uniform======================================

	void ShaderManager::BroadCastUniform1F(const char * pUniformName, float pValue) noexcept
	{
		for (auto& i : m_Shaders)
		{
			i.second.SetUniformFloat1(pUniformName, pValue);
		}
	}
	void ShaderManager::BroadCastUniform2F(const char * pUniformName, float pValue1, float pValue2, float pValue3) noexcept
	{
		for (auto& i : m_Shaders)
		{
			i.second.SetUniformFloat2(pUniformName, pValue1, pValue2);
		}
	}

	void ShaderManager::BroadCastUniform3F(const char * pUniformName, float pValue1, float pValue2, float pValue3) noexcept
	{
		for (auto& i : m_Shaders)
		{
			i.second.SetUniformFloat3(pUniformName, pValue1, pValue2, pValue3);
		}
	}

	void ShaderManager::BroadCastUniform3F(const char * pUniformName, glm::vec3 pValues) noexcept
	{
		BroadCastUniform3F(pUniformName, pValues.x, pValues.y, pValues.z);
	}

	void ShaderManager::BroadCastUniform1I(const char * pUniformName, int32 pValue) noexcept
	{
		for (auto& i : m_Shaders)
		{
			i.second.SetUniformInt1(pUniformName, pValue);
		}
	}
	void ShaderManager::BroadCastUniform2I(const char * pUniformName, int32 pValue1, int32 pValue2, int32 pValue3) noexcept
	{
		for (auto& i : m_Shaders)
		{
			i.second.SetUniformInt2(pUniformName, pValue1, pValue2);
		}
	}

	void ShaderManager::BroadCastUniform3I(const char * pUniformName, int32 pValue1, int32 pValue2, int32 pValue3) noexcept
	{
		for (auto& i : m_Shaders)
		{
			i.second.SetUniformInt3(pUniformName, pValue1, pValue2, pValue3);
		}
	}

	void ShaderManager::BroadCastUniformMat4(const char * pUniformName, glm::mat4 & pValue)
	{
		for (auto& i : m_Shaders)
		{
			i.second.SetUniformMat4(pUniformName, pValue);
		}
	}
};