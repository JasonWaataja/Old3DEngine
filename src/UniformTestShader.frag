#version 330
out vec4 outColor;
uniform vec3 uniformColor;
void main()
{
	outColor = vec4(uniformColor, 1);
}