#version 330 core

out vec4 FragColor;

uniform vec3 lightColor;
uniform vec3 boxColor;

void main()
{
	FragColor = vec4(lightColor * boxColor, 1.0f);
}