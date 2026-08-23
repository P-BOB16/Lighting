#version 330 core

in vec3 Normal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 FragColor;

struct Material 
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform sampler2D decTex;
uniform vec3 boxColor;
uniform vec3 camPos;
uniform Material material;
uniform Light light;

void main()
{
	//caluculation for ambient lighting
	vec3 ambiant = material.ambient * light.ambient;

	//calculation for diffused lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuse = light.diffuse * (diff * material.diffuse);

	//calculation for specular lighting
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflection = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflection), 0.0), material.shininess);
	vec3 specular = light.specular * (spec * material.specular);

	//result variable
	vec3 result = diffuse + ambiant + specular;
	//FragColor = texture(decTex, texCoord) * vec4(result, 1.0f);
	FragColor = vec4(result, 1.0f);
}