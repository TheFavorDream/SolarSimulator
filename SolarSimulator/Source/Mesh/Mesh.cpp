#include "Mesh.h"


namespace Simulator
{
	Mesh::Mesh(const std::vector<Vertex>& pVertices)
	{
		SetUp(pVertices, std::vector<uint16>());
	}

	Mesh::Mesh(const std::vector<Vertex>& pVertices, const std::vector<uint16>& pIndices)
	{
		SetUp(pVertices, pIndices);
	}

	Mesh::Mesh(Mesh&& Other) noexcept
	{
		m_Vertices = Other.m_Vertices;
		m_Indices = Other.m_Indices;
			
		m_Model = Other.m_Model;
		m_VBO = std::move(Other.m_VBO);
		m_VAO = std::move(Other.m_VAO);
		m_EBO = std::move(Other.m_EBO);
		
	}

	Mesh::~Mesh()
	{
		Free();
	}


	int Mesh::LoadMesh(const std::string & pMeshPath)
	{
		
		LoadGLB(pMeshPath);
		Free();
		return 0;
	}


	int  Mesh::Free()
	{
		m_Vertices.clear();
		m_Indices.clear();
		m_Buffers.clear();



		return 0;
	}

	void Mesh::Render(const Shader& pShader) noexcept
	{
		pShader.Bind();


		pShader.SetUniformMat4("Model", m_Model);

		m_VAO.Bind();
		if (m_EBO.GetCount() != 0)
			glDrawElements(GL_TRIANGLES, m_EBO.GetCount(), GL_UNSIGNED_SHORT, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, m_VBO.GetVertexNumbers());
		m_VAO.Unbind();
	}

	int Mesh::LoadGLB(const std::string & pFilePath)
	{
		//Opening and Reading the model binary file:
		std::ifstream Source(pFilePath, std::ios::in | std::ios::binary);
		if (!Source.is_open())
		{
			Log::GetSelf()->SetError("Unable to Open Model File: %s", pFilePath);
			return 1;
		}

		Source.seekg(0, Source.end);
		uint32 FileSize = Source.tellg();
		Source.seekg(0, Source.beg);

		std::string Data; Data.resize(FileSize);
		Source.read(&Data[0], FileSize);
		Source.close();

		//Slicing the binary Data into chunks:


		//Processing the header:
		std::string Header = Data.substr(0, 12); //Reading the Header
		uint32 Magic;
		uint32 Length;

		memcpy((void*)&Magic, (void*)&Header.substr(0, 4), 4);
		memcpy((void*)&Length, (void*)&Header.substr(8, 4), 4);


		//Check the magic number
		if (Magic != GLB_MAGIC)
		{
			Log::GetSelf()->SetError("Invalid file. unmatching magic number");
			return 1;
		}
		Log::GetSelf()->SetInfo("Read GLB File. Length:%i bytes", Length);

		//Processing the Json:

		uint32 JsonChunkLength = 0;
		memcpy((void*)&JsonChunkLength, (void*)&Data.substr(12, 4), 4);

		std::string JsonData = Data.substr(20, JsonChunkLength);

		Json Root = Json::parse(JsonData);

		//Processing binary Chunk:

		uint32 BinaryChunkSize = 0;
		memcpy((void*)&BinaryChunkSize, (void*)&Data.substr(JsonChunkLength + 20, 4), 4);

		if (BinaryChunkSize + JsonChunkLength + 28 != Length)
		{
			Log::GetSelf()->SetError("Corrupted Data. unmatched chunk sized with file length");
		}

		m_Buffers[0] = Data.substr(28 + JsonChunkLength, BinaryChunkSize);

		if (LoadNodes(Root, Root["scenes"][0]) != 0)
		{
			return 1;
		}

		return 0;
	}

	int Mesh::LoadNodes(Json & pRoot, Json & pNodes)
	{
		for (auto &i : pNodes["nodes"])
		{
			if (LoadMesh(pRoot, pRoot["nodes"][int(i)]["mesh"]) != 0)
			{
				Log::GetSelf()->SetInfo("Failed to Load Mesh");
				continue;
			}
		}
	}

	int Mesh::LoadMesh(Json & pRoot, int pMeshIndex)
	{

		uint32 AccessorPosition = (uint32)pRoot["meshes"][pMeshIndex]["primitives"][0]["attributes"]["POSITION"];
		uint32 AccessorNormals = (uint32)pRoot["meshes"][pMeshIndex]["primitives"][0]["attributes"]["NORMAL"];
		uint32 AccessorTexCoords = (uint32)pRoot["meshes"][pMeshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
		uint32 AccessorIndcies = (uint32)pRoot["meshes"][pMeshIndex]["primitives"][0]["indices"];

		std::vector<Vertex> Vertices;

		std::vector<glm::vec3> Positions = RetriveVec3(pRoot, AccessorPosition);
		std::vector<glm::vec3> Normals = RetriveVec3(pRoot, AccessorNormals);
		std::vector<glm::vec2> TexCoords = RetriveVec2(pRoot, AccessorTexCoords);

		//Retriving indcies:
		std::string IndicesData;
		GetRawData(IndicesData, pRoot, (uint32)pRoot["accessors"][AccessorIndcies]["bufferView"]);
		uint32 IndicesCount = (uint32)pRoot["accessors"][AccessorIndcies]["count"];
		uint32 TypeSize = 2;

		std::vector<uint16> Indices;

		for (int i = 0, Offset = 0; i < IndicesCount; i++)
		{
			uint16 Index;
			std::string V = IndicesData.substr(Offset, 2);
			memcpy(&Index, &V[0], 2);
			Indices.push_back(Index);
			Offset += 2;
		}


		//Combining Attribs:
		for (int i = 0; i < Positions.size(); i++)
		{
			Vertices.push_back({ Positions[i], Normals[i], TexCoords[i] });
		}

		SetUp(Vertices, Indices);

		return 0;
	}

	int Mesh::GetRawData(std::string & pData, Json & pRoot, uint32 pBufferIndex)
	{
		uint32 Buffer = pRoot["bufferViews"][pBufferIndex]["buffer"];
		uint32 Offset = pRoot["bufferViews"][pBufferIndex]["byteOffset"];
		uint32 Length = pRoot["bufferViews"][pBufferIndex]["byteLength"];

		if (m_Buffers.find(Buffer) == m_Buffers.end())
		{
			Log::GetSelf()->SetError("Invalid Buffer Index");
			return 1;
		}
		pData = m_Buffers[Buffer].substr(Offset, Length);
		return 0;
	}

	std::vector<glm::vec3> Mesh::RetriveVec3(Json & pRoot, uint32 pAccessorName)
	{
		//We check first if it is the correct data type
		if (pRoot["accessors"][pAccessorName]["type"] != "VEC3")
			return std::vector<glm::vec3>();


		//Retrive some values
		uint32 Count = (uint32)pRoot["accessors"][pAccessorName]["count"];
		uint32 BufferIndex = (uint32)pRoot["accessors"][pAccessorName]["bufferView"];

		uint32 ComponentPerVertex = 3;
		uint32 SizeOfComponent = sizeof(float);

		std::vector<glm::vec3> Vecs;

		std::string Data;
		GetRawData(Data, pRoot, BufferIndex);

		uint32 Offset = 0;

		//Slicing Data
		for (int i = 0; i < Count; i++)
		{
			glm::vec3 Current;
			std::string Slice = Data.substr(Offset, ComponentPerVertex*SizeOfComponent);
			memcpy((void*)&Current, (void*)&Slice[0], ComponentPerVertex*SizeOfComponent);
			Offset += (ComponentPerVertex * SizeOfComponent);
			Vecs.push_back(Current);
		}

		return Vecs;
	}

	std::vector<glm::vec2> Mesh::RetriveVec2(Json & pRoot, uint32 pAccessorName)
	{
		if (pRoot["accessors"][pAccessorName]["type"] != "VEC2")
			return std::vector<glm::vec2>();

		//Retrive some values
		uint32 Count = (uint32)pRoot["accessors"][pAccessorName]["count"];
		uint32 BufferIndex = (uint32)pRoot["accessors"][pAccessorName]["bufferView"];

		uint32 ComponentPerVertex = 2;
		uint32 SizeOfComponent = sizeof(float);

		std::vector<glm::vec2> Vecs;

		std::string Data;
		GetRawData(Data, pRoot, BufferIndex);

		uint32 Offset = 0;

		//Slicing Data
		for (int i = 0; i < Count; i++)
		{
			glm::vec2 Current;
			std::string Slice = Data.substr(Offset, ComponentPerVertex*SizeOfComponent);
			memcpy((void*)&Current, (void*)&Slice[0], ComponentPerVertex*SizeOfComponent);
			Offset += (ComponentPerVertex * SizeOfComponent);
			Vecs.push_back(Current);
		}

		return Vecs;
	}


	void Mesh::SetUp(const std::vector<Vertex>& pVertices, const std::vector<uint16>& pIndices)
	{
		m_Vertices = pVertices;
		m_Indices  = pIndices;



		m_VAO.CreateVertexArray();
		m_VAO.Bind();

		m_VBO.InitBuffer(pVertices);
		m_EBO.InitBuffer(pIndices);

		m_VAO.AddLayout(GL_FLOAT, 3, GL_FALSE);
		m_VAO.AddLayout(GL_FLOAT, 3, GL_FALSE);
		m_VAO.AddLayout(GL_FLOAT, 2, GL_FALSE);
		m_VAO.LoadLayout(m_VBO, m_EBO);
		m_VAO.Unbind();

		m_Vertices.clear();
		m_Indices.clear();
	}

};