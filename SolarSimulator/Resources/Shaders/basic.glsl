//This is a comment
#type:Vertex
#version 330 core

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normals;
layout(location=2) in vec2 TexCoords;

out vec3 aNormals;
out vec2 aTexCoords;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	aNormals = Normals;
	aTexCoords = TexCoords;
	gl_Position =  Model * vec4(Position, 1.0f);
}

#type:Fragment

#version 330 core

in vec3 aNormals;
in vec2 aTexCoords;

out vec4 FragColor;
void main ()
{
	FragColor=vec4(0.5f, 0.0f, 0.9f, 1.0f);
}
