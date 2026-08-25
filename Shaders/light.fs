#version 330 core

in vec2 texCoord;

uniform sampler2D autoTex;
uniform vec3 reflectColor;

out vec4 FragColor;
void main()
{
   // FragColor = texture(autoTex, texCoord);
	FragColor = vec4(reflectColor, 1.0f);
}