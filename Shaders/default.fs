#version 330 core

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
uniform float time;

void main()
{		
	vec2 matrixCoord= texCoord;
	matrixCoord.y  -= time * 0.5;
	vec3 glow		= vec3(texture(material.emission, matrixCoord));

	//caluculation for ambient lighting
	vec3 ambiant	= light.ambient * vec3(texture(material.diffuse, texCoord));

	//calculation for diffused lighting
	vec3 norm		= normalize(Normal);
	vec3 lightDir	= normalize(light.position - fragPos);
	float diff		= max(dot(lightDir, norm), 0.0f);
	vec3 diffuse	= light.diffuse * diff * vec3(texture(material.diffuse, texCoord));

	//calculation for specular lighting
	vec3 viewDir	= normalize(camPos - fragPos);
	vec3 reflection = reflect(-lightDir, norm);
	float spec		= pow(max(dot(viewDir, reflection), 0.0), material.shininess);
	vec3 specular	= light.specular * spec * vec3(texture(material.specular, texCoord));

	//Removing the borders of the matrix as per the second image
	float borderMask = step(0.1f, texture(material.specular, texCoord).r); 
	float woodMask   = 1.0f - borderMask;
	float pulse		 = (cos(time * 3.0f) + 1.0f) / 2.0f;
	vec3 emmit		 = woodMask * glow * pulse;

	//result variable
	vec3 result = diffuse + ambiant + specular + emmit;

	//FragColor = texture(decTex, texCoord) * vec4(result, 1.0f);
	//FragColor = mix(texture(material.specular, texCoord), texture(material.diffuse, texCoord), 0.5);

	FragColor = vec4(result, 1.0f);
}