#pragma once

#include "Mesh.h"
#include "../Renderer/Shader.h"
#include "../Camera/Camera.h"
#include "../Renderer/Texture.h"	

#include <vector>
#include <string>
#include <fstream>
#include "../../3rdParty/JsonParser/Json.h"
#include "../LogSys/Log.h"
#include "../Core.h"

namespace Simulator
{

	class Model
	{
	public:

		 Model() = default;
		 Model(std::string pModelFilePath);
		 ~Model();

		 //Loading model
		 int LoadModel(std::string pModelFilePath);
		 int FreeModel();

		void Render(Shader& pShader, Camera& pCamera);



		inline glm::mat4& GetModelMatrix() { return m_ModelTransform; }

	private:

		int LoadNodes(Json& pRoot, Json& pNodes);
		int LoadMeshes(Json& pRoot, int pMeshIndex);
		int GetRawData(std::string& pData, Json& pRoot, uint32 pBufferIndex);

		int ReadRawModelData(Json& pRoot);
		int ProcessMaterials(Json& pRoot);

		std::vector<glm::vec3> RetriveVec3(Json& pRoot, uint32 pAccessorName);
		std::vector<glm::vec2> RetriveVec2(Json& pRoot, uint32 pAccessorName);


	private:

		std::vector<Mesh>      m_Mesh;
		glm::mat4 m_ModelTransform = glm::mat4(1.0f);

		//All the unstructured model buffers stored here for future use:
		std::unordered_map<int, std::string> m_RawBuffers;
		std::unordered_map<uint32, Texture2D> m_Textures;
		std::string m_ParentDir;
	};

};
