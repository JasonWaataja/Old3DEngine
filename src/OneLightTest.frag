#version 330
in vec3 position;
in vec2 texCoord;
in vec3 normal;
out vec4 outColor;
uniform sampler2D textureToUse;

void main()
{
	vec4 textureColor = texture(textureToUse, texCoord);
	vec3 finalColor = textureColor.xyz;
	outColor = vec4(finalColor, 1);
}