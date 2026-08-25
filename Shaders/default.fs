#version 330 core

in vec3 Normal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 FragColor;

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light
{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 camPos;
uniform Material material;
uniform Light light;

void main()
{
	//caluculation for ambient lighting
	vec3 ambiant = light.ambient * vec3(texture(material.diffuse, texCoord));

	//calculation for diffused lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - fragPos);
	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));

	//calculation for specular lighting
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflection = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflection), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));

	//result variable
	vec3 result = diffuse + ambiant + specular;
	//FragColor = texture(decTex, texCoord) * vec4(result, 1.0f);
	FragColor = vec4(result, 1.0f);
}