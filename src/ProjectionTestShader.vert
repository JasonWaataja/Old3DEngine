#version 330
in vec4 inCoord;
uniform mat4 matrixToUse;
void main()
{
	vec4 outCoord;
	outCoord = matrixToUse * inCoord;
	gl_Position = outCoord;
}