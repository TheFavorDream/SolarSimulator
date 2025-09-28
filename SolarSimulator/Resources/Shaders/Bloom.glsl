#type:Vertex
#version 330 core

layout(location=0) in vec2 Position;
layout(location=2) in vec2 TexCoords;

out vec2 aTexCoords;

void main()
{
	aTexCoords = TexCoords;
	gl_Position = vec4(Position,0.0f,  1.0f);
}

#type:Fragment

#version 330 core

in vec2 aTexCoords;
uniform sampler2D Texture;	

layout(location=0) out vec4 FragColor;
layout(location=1) out vec4 BrightColor;


void main ()
{

	FragColor = texture(Texture, aTexCoords);
	float Brightness = dot(FragColor.rgb, vec3(0.2126, 0.7152, 0.722)*1.3f);

	if (Brightness > 1.0f)
	{
		BrightColor = FragColor;
	}
	else
	{
		BrightColor = vec4(0);
	}
}
