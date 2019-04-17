#version 430 core


layout(location = 0) in vec4 vPosition;
uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);

void main()
{
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPosition.x, vPosition.y, vPosition.z, 1.0);
}