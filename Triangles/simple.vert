#version 430 core

layout(location = 0) in vec4 vPosition;

uniform mat4 modelMatrix;
uniform mat4 projectionViewMatrix;

void main()
{
	gl_Position = projectionViewMatrix * modelMatrix * vec4(vPosition.x, vPosition.y, vPosition.z, vPosition.w);
}