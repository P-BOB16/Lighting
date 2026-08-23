#version 330 core

in vec3 Normal;
in vec3 fragPos;

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 boxColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
	//caluculation for ambiant lighting
	float ambiantStrength = 0.1;
	vec3 ambiant = ambiantStrength * lightColor;

	//calculation for diffused lighting
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - fragPos);
	float diff = max(dot(lightDir, norm), 0.0f);
	vec3 diffuse = diff * lightColor;

	//calculation for specular lighting
	float specularStrength = 0.5f;
	vec3 viewDir = normalize(camPos - fragPos);
	vec3 reflection = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflection), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	//result variable
	vec3 result = (diffuse + ambiant + specular) * boxColor;

	FragColor = vec4(result , 1.0f);
}