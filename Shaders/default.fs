#version 330 core
#define NR_POINT_LIGHTS 4

in vec3 Normal;
in vec3 fragPos;
in vec2 texCoord;

out vec4 FragColor;

struct Material 
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct DirLight 
{
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight 
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform vec3 camPos;
uniform Material material;
uniform float time;
uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{		
	vec3 viewPos = vec3(camPos);
	//emmision calculation
	vec2 matrixCoord  = texCoord;
	matrixCoord.y    -= time * 0.5;
	vec3 glow		  = vec3(texture(material.emission, matrixCoord));
	//Removing the borders of the matrix as per the second image
	float borderMask  = step(0.1f, texture(material.specular, texCoord).r); 
	float woodMask    = 1.0f - borderMask;
	float pulse		  = (cos(time * 3.0f) + 1.0f) / 2.0f;
	vec3 emmit		  = woodMask * glow * pulse;

	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - fragPos);

	vec3 result = CalcDirLight(dirLight, norm, viewDir);
	
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
		result +=  CalcPointLight(pointLights[i], norm, fragPos, viewDir);

		FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	//diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	//speular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	//diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	//specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	//attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	//combine results
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, texCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoord));
	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}