#pragma once
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ElementBuffer.h"
#include "../Renderer/Shader.h"
#include "../Camera/Camera.h"
#include "../Renderer/Texture.h"


#include <vector>
#include <fstream>
#include <unordered_map>
#include <mutex>
#include "../../3rdParty/JsonParser/Json.h"


namespace Simulator
{
	class Mesh
	{
	public:

		Mesh() = default;
		Mesh(const std::vector<Vertex>& pVertices);
		Mesh(const std::vector<Vertex>& pVertices, const std::vector<uint16>& pIndices);
		Mesh(Mesh&& Other) noexcept; //Move Constructor
		~Mesh();


		int LoadMesh(const std::string& pMeshPath);
		int LoadGLB(const std::string& pFilePath);
		int Free();

		void Render(const Shader& pShader) noexcept;

		inline glm::mat4& GetModelMatrix() { return m_Model; }

		void SetUp(const std::vector<Vertex>& pVertices, const std::vector<uint16>& pIndices);

	private:

		int LoadNodes(Json& pRoot, Json& pNodes);
		int LoadMesh(Json& pRoot, int pMeshIndex);

		int GetRawData(std::string& pData, Json& pRoot, uint32 pBufferIndex);
		std::vector<glm::vec3> RetriveVec3(Json& pRoot, uint32 pAccessorName);
		std::vector<glm::vec2> RetriveVec2(Json& pRoot, uint32 pAccessorName);


	private:
		VertexArray  m_VAO;
		VertexBuffer m_VBO;
		ElementBuffer m_EBO;

		glm::mat4 m_Model = glm::mat4(1.0f);

		std::vector<Vertex> m_Vertices;
		std::vector<uint16> m_Indices;


		std::mutex m_Mutex;
		std::unordered_map<uint32, std::string> m_Buffers;
	};
};