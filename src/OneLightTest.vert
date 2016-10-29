#version 330
layout(location = 0) in vec3 inCoord;
layout(location = 1) in vec2 inTexCoord;
layout(location = 2) in vec3 inNormal;
out vec3 position;
out vec2 texCoord;
out vec3 normal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 normalMatrix;
void main()
{
	vec4 cameraSpaceCoord = modelViewMatrix * vec4(inCoord, 1);
	gl_Position =  projectionMatrix * cameraSpaceCoord;
	position = cameraSpaceCoord.xyz;
	texCoord = inTexCoord;
	normal = (normalMatrix * vec4(inNormal, 0)).xyz;
}