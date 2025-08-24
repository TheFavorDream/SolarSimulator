#pragma once

#include "../Core.h"
#include "../LogSys/Log.h"

#include "../Mesh/Mesh.h"
#include "../Renderer/Texture.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Renderer.h"
#include "../Camera/Camera.h"

#include <vector>

namespace Simulator
{

	class SkyBox
	{
	public:

		 SkyBox(std::string pTexturePath);
		 SkyBox() = default;
		~SkyBox();

		void CreateSkyBox(std::string pSubPath, const std::vector<std::string>& pFiles);
		void FreeSkyBox();

		void RenderSkyBox();

	private:

		std::vector<Vertex> m_Vertices = 
		{
			{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f,  1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f,  1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f, -1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3(-1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)},
			{glm::vec3( 1.0f, -1.0f,  1.0f), glm::vec3(0.0f), glm::vec2(0.0)}
		};

		std::string m_VertexShader =
			"#version 330 core\n"
			"layout(location=0) in vec3 aPos;\n"
			"uniform mat4 Model;\n"
			"uniform mat4 Projection;\n"
			"uniform mat4 View;\n"
			"out vec3 TexCoords;\n"
			"void main()\n"
			"{\n"
			"mat4 view = mat4(mat3(View));"
			"TexCoords = aPos;\n"
			"vec4 pos = Projection * view * Model * vec4(aPos, 1.0);\n"
			"gl_Position = pos.xyww;\n"
			"}\n";

		std::string m_FragmentShader =
			"#version 330 core\n"
			"out vec4 FragColor;\n"
			"in vec3 TexCoords;\n"
			"uniform samplerCube skybox;\n"
			"void main()\n"
			"{\n"
			"FragColor = texture(skybox, TexCoords);\n"
			"}\n";

		Mesh m_Cube; //Mesh containg the cube that the sky box is being draw on
		TextureCube m_CubeMap; // Cube map of textures
		uint32 m_Shader; // Sky box shader
	};

};