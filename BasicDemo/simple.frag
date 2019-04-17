#version 430 core

uniform vec4 inputColor = vec4(1.0, 1.0, 1.0, 1.0);
out vec4 fColor;

void main()
{
	fColor = inputColor;
}