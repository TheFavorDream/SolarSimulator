//This is a comment
#type:Vertex
#version 330 core

layout(location=0) in vec3 Position;
layout(location=1) in vec3 Normals;
layout(location=2) in vec2 TexCoords;

out vec3 aNormals;
out vec2 aTexCoords;
out vec3 aFragPos;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main()
{
	aNormals = mat3(Model) * Normals;
	aTexCoords = TexCoords;
	aFragPos = vec3(Model * vec4(Position, 1.0f));
	gl_Position = Projection * View * Model * vec4(Position, 1.0f);
}

#type:Fragment

#version 330 core

in vec3 aNormals;
in vec2 aTexCoords;
in vec3 aFragPos;

uniform sampler2D Texture;	

struct Light
{
	vec3 LightPosition;
	vec3 LightColor;

	float Ambient;

	float Constant;
	float Linear;
	float Quadratic;

};

uniform Light light;

out vec4 FragColor;


void main ()
{

	vec3 Ambient = light.Ambient * light.LightColor;
	
	vec3 LightDir = normalize(light.LightPosition - aFragPos);
	float Diff = max(dot(normalize(aNormals), LightDir), 0.0);
	vec3 Diffuse = Diff * light.LightColor;


	float Dis = length(light.LightPosition - aFragPos);
	float att = 1.0 / (light.Constant + light.Linear*Dis + light.Quadratic*(Dis*Dis));

	FragColor = vec4((Ambient+Diffuse)*att, 1.0f) * texture(Texture, aTexCoords);

}
