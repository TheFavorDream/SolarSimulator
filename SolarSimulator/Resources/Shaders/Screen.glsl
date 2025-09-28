
//Frame Buffer Shader

#type:Vertex
#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
    TexCoords = aTexCoords;
}  

#type:Fragment

#version 330 core

out vec4 FragColor;
in vec2 TexCoords;

uniform sampler2D screenTexture;
uniform sampler2D BloomEffect;

uniform bool UseBloom=true;

uniform float Gamma;

void main()
{

	vec3 Hdr = texture(screenTexture, TexCoords).rgb;
	vec3 Bloom = texture(BloomEffect, TexCoords).rgb;

	if (UseBloom)
		Hdr += Bloom;

	vec3 ToneMapped = pow(Hdr / (Hdr + vec3(1.0f)), vec3(1.0f/Gamma));
	FragColor = vec4(ToneMapped, 1.0f);

}
  