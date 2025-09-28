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
	gl_Position = Projection * View * Model * vec4(Position, 1.0f);
}

#type:Fragment

#version 330 core

out vec4 FragColor;

in vec3 aNormals;
in vec2 aTexCoords;
uniform sampler2D Texture;	


uniform float Intensity;

void main ()
{
	vec3 Res = texture(Texture, aTexCoords).rgb*Intensity;
	FragColor = vec4(Res, 1.0f);
}
