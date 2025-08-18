#include "Model.h"
#include "Model.h"
#include "Model.h"
#include "Model.h"
#include "Model.h"
#include "Model.h"

namespace Simulator
{

	Model::Model(std::string pModelFilePath)
	{
		LoadModel(pModelFilePath);
	}

	Model::~Model()
	{
		FreeModel();
	}

	void Model::Render(Shader & pShader, Camera & pCamera)
	{
		for (auto &i : m_Mesh)
		{
			i.Render(pShader, pCamera, m_ModelTransform);
		}
	}

	int Model::LoadModel(std::string pModelFilePath)
	{
		//Reading and Parsing the gltf file:
		std::ifstream ModelSource(pModelFilePath, std::ios::in);
	
		if (ModelSource.fail())
		{
			Log::GetSelf()->SetError("Cannot Open Model at %s", pModelFilePath);
			return 1; //Exit
		}
		Json Data = Json::parse(ModelSource);
		ModelSource.close();

		m_ParentDir = pModelFilePath.substr(0, pModelFilePath.find_last_of("\\"));
		Log::GetSelf()->SetInfo("Loading Model from %s", m_ParentDir);


		//Loading the Raw Datas in memory:
		ReadRawModelData(Data);

		//Process the Json file and Scene Structure
		if (LoadNodes(Data, Data["scenes"][0]) != 0)
		{
			return 1;
		}


		m_RawBuffers.clear();

		//Log::GetSelf()->DebugPrint(Data.dump(4));
		return 0;
	}

	int Model::LoadNodes(Json& pRoot, Json& pNodes)
	{
		Log::GetSelf()->SetInfo("Model: %s", std::string(pNodes["name"]));

		for (auto &i : pNodes["nodes"])
		{
			Log::GetSelf()->SetInfo("node: %i", int(i));
			if (LoadMeshes(pRoot, pRoot["nodes"][int(i)]["mesh"]) != 0)
			{
				Log::GetSelf()->SetInfo("Failed to Load Mesh");
				continue;
			}


		}

		return 0;
	}

	int Model::LoadMeshes(Json& pRoot, int pMeshIndex)
	{

		uint32 AccessorPosition = (uint32)pRoot["meshes"][pMeshIndex]["primitives"][0]["attributes"]["POSITION"];
		uint32 AccessorNormals = (uint32)pRoot["meshes"][pMeshIndex]["primitives"][0]["attributes"]["NORMAL"];
		uint32 AccessorTexCoords = (uint32)pRoot["meshes"][pMeshIndex]["primitives"][0]["attributes"]["TEXCOORD_0"];
		uint32 AccessorIndcies = (uint32)pRoot["meshes"][pMeshIndex]["primitives"][0]["indices"];

		std::vector<Vertex> Vertices;

		//Retriving Position Data:
		std::string PositionData;
		GetRawData(PositionData, pRoot, (uint32)pRoot["accessors"][AccessorPosition]["bufferView"]);

		uint32 ComponentSize = 4;
		uint32 ComponentPerVertex = 3;
		uint32 Count = (uint32)pRoot["accessors"][AccessorPosition]["count"];

		for (int i = 0, Offset= 0; i < Count; i++)
		{
			glm::vec3 Position;
			std::string V = PositionData.substr(Offset,12);
			memcpy(&Position, &V[0], ComponentSize*ComponentPerVertex);
			Offset += (ComponentSize * ComponentPerVertex);
			Vertices.push_back({Position, glm::vec3(0.0f), glm::vec2(0.0f)});
		}

		//Retriving Normals:

		std::string NormalData;
		GetRawData(NormalData, pRoot, (uint32)pRoot["accessors"][AccessorNormals]["bufferView"]);

		for (int i = 0, Offset = 0; i < Count; i++)
		{
			glm::vec3 Position;
			std::string V = NormalData.substr(Offset, 12);
			memcpy(&Position, &V[0], ComponentSize*ComponentPerVertex);
			Offset += (ComponentSize * ComponentPerVertex);
			Vertices[i].Normal = Position;
		}
		

		//Retriving indcies:
		std::string IndicesData;
		GetRawData(IndicesData, pRoot, (uint32)pRoot["accessors"][AccessorIndcies]["bufferView"]);

		uint32 IndicesCount = (uint32)pRoot["accessors"][AccessorIndcies]["count"];
		uint32 TypeSize = 2;

		std::vector<uint16> Indices;

		for (int i = 0, Offset=0; i < IndicesCount; i++)
		{
			uint16 Index;
			std::string V = IndicesData.substr(Offset, 2);
			memcpy(&Index, &V[0], 2);
			Indices.push_back(Index);
			Offset += 2;
		}


		Mesh New(Vertices, Indices);

		//Retriving Transforms:

		//New.GetMatrix() = glm::scale(New.GetMatrix(), glm::vec3(pRoot["nodes"][pMeshIndex]["scale"][0], pRoot["nodes"][pMeshIndex]["scale"][0], pRoot["nodes"][pMeshIndex]["scale"][0]));

		m_Mesh.push_back(std::move(New));

		return 0;
	}

	int Model::GetRawData(std::string & pData, Json& pRoot, uint32 pBufferIndex)
	{
		uint32 Buffer = pRoot["bufferViews"][pBufferIndex]["buffer"];
		uint32 Offset = pRoot["bufferViews"][pBufferIndex]["byteOffset"];
		uint32 Length = pRoot["bufferViews"][pBufferIndex]["byteLength"];

		if (m_RawBuffers.find(Buffer) == m_RawBuffers.end())
		{
			Log::GetSelf()->SetError("Invalid Buffer Index");
			return 1;
		}
		pData = m_RawBuffers[Buffer].substr(Offset, Length);
		return 0;
	}

	int Model::ReadRawModelData(Json& pRoot)
	{
		std::string Temp;
		int index = 0;

		for (auto&i : pRoot["buffers"])
		{

			Temp.clear();
			Temp = m_ParentDir + "\\" + std::string(i["uri"]);
			uint32 ByteLength = uint32(i["byteLength"]);

			std::ifstream Source(Temp, std::ios::in | std::ios::binary);

			if (Source.fail())
			{
				Log::GetSelf()->SetError("Cannot Open Model File %s", Temp);
				continue;
			}

			Temp.clear();
			Temp.resize(ByteLength);
			Source.read(&Temp[0], ByteLength);
			Source.close();

			m_RawBuffers[index] = Temp;
			index ++;

			Log::GetSelf()->SetInfo("Load %i bytes to memory", ByteLength);
		}
		return 0;
	}
	int Model::FreeModel()
	{
		return 0;
	}


};