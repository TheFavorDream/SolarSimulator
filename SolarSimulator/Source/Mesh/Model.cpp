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
			int32 Mat = i.GetMaterialIndex();
			if (Mat != -1)
			{
				m_Textures[Mat].Bind(0);
				pShader.SetUniformInt1("Texture", 0);
			}

			i.Render(pShader, pCamera, m_ModelTransform);

			if (Mat != -1)
			{
				m_Textures[Mat].Unbind();
			}
		}
		pShader.Unbind();
	}

	int Model::LoadModel(std::string pModelFilePath)
	{

		std::string Prefix = pModelFilePath.substr(pModelFilePath.find_last_of(".")+1);

		if (Prefix == "gltf")
		{
			LoadGLTF(pModelFilePath);
		}
		else if (Prefix == "glb")
		{
			LoadGLB(pModelFilePath);
		}
		else
		{
			Log::GetSelf()->SetError("Invalid model file: %s", Prefix);
		}

		FreeModel();
		return 0;
	}

	int Model::LoadGLTF(const std::string & pFilePath)
	{
		//Reading and Parsing the gltf file:
		std::ifstream ModelSource(pFilePath, std::ios::in);

		if (ModelSource.fail())
		{
			Log::GetSelf()->SetError("Cannot Open Model at %s", pFilePath);
			return 1; //Exit
		}
		Json Data = Json::parse(ModelSource);
		ModelSource.close();

		m_ParentDir = pFilePath.substr(0, pFilePath.find_last_of("\\"));
		Log::GetSelf()->SetInfo("Loading Model from %s", pFilePath);


		//Loading the Raw Datas in memory:
		ReadRawModelData(Data);
		//Loading Textures
		ProcessMaterials(Data);

		//Process the Json file and Scene Structure
		if (LoadNodes(Data, Data["scenes"][0]) != 0)
		{
			return 1;
		}
		return 0;
	}

	int Model::LoadGLB(const std::string & pFilePath)
	{

		//Opening and Reading the model binary file:
		std::ifstream Source(pFilePath, std::ios::in | std::ios::binary);
		if (!Source.is_open())
		{
			Log::GetSelf()->SetError("Unable to Open Model File: %s", pFilePath);
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
		memcpy((void*)&BinaryChunkSize, (void*)&Data.substr(JsonChunkLength+20, 4), 4);
		
		if (BinaryChunkSize + JsonChunkLength + 28 != Length)
		{
			Log::GetSelf()->SetError("Corrupted Data. unmatched chunk sized with file length");
		}
	
		m_RawBuffers[0] = Data.substr(28+JsonChunkLength, BinaryChunkSize);

		ProcessMaterials(Root);
		
		if (LoadNodes(Root, Root["scenes"][0]) != 0)
		{
			return 1;
		}

		return 0;
	}

	int Model::LoadNodes(Json& pRoot, Json& pNodes)
	{
		Log::GetSelf()->SetInfo("Model: %s", std::string(pNodes["name"]));

		for (auto &i : pNodes["nodes"])
		{
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
		int32 AccessorMaterial = (int32)pRoot["meshes"][pMeshIndex]["primitives"][0].value("material", -1);

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

		for (int i = 0, Offset=0; i < IndicesCount; i++)
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
			Vertices.push_back({Positions[i], Normals[i], TexCoords[i]});
		}

		Mesh New(Vertices, Indices, AccessorMaterial);

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

	int Model::ProcessMaterials(Json & pRoot)
	{
		int index = 0;
		for (auto &i : pRoot["textures"])
		{
			uint32 Sampler = (uint32)i["sampler"];
			GLenum Min = pRoot["samplers"][Sampler]["minFilter"];
			GLenum Mag = pRoot["samplers"][Sampler]["magFilter"];


			uint32 Source = (uint32)i["source"];
			
			//if there is a uri we load it, and if not we read from bufferview
			if (pRoot["images"][Source].find("uri") != pRoot["images"][Source].end())
			{
				std::string Path = m_ParentDir + "\\" + std::string(pRoot["images"][Source]["uri"]);
				m_Textures[index].CreateTexture(Path, Min, Mag, false);
			}
			else
			{
				std::string Texture;
				GetRawData(Texture, pRoot, (uint32)pRoot["images"][Source]["bufferView"]);
				const char* Data = Texture.c_str();
				m_Textures[index].CreateTextureFromMemory((uint8*)Data, Texture.length() , Min, Mag, false);
			}

			index++;
		}
		return 0;
	}

	std::vector<glm::vec3> Model::RetriveVec3(Json & pRoot, uint32 pAccessorName)
	{
		//We check first if it is the correct data type
		if (pRoot["accessors"][pAccessorName]["type"] != "VEC3")
			return std::vector<glm::vec3>();


		//Retrive some values
		uint32 Count =       (uint32)pRoot["accessors"][pAccessorName]["count"];
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

	std::vector<glm::vec2> Model::RetriveVec2(Json & pRoot, uint32 pAccessorName)
	{
		if (pRoot["accessors"][pAccessorName]["type"] != "VEC2")
			return std::vector<glm::vec2> ();

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





	int Model::FreeModel()
	{
		m_RawBuffers.clear();
		return 0;
	}


};