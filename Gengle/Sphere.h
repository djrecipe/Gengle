#pragma once
#ifndef __OmniSphere__
#define __OmniSphere__

#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "VertexArray.h"
#include "Buffer.h"

class Sphere : GElement
{
private:
public:
	static const GLuint Sphere::NumVertices = 8;
	static const GLuint Sphere::NumIndices = 36;
	Sphere::Sphere(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void Sphere::Draw(void);
	void Sphere::Prepare(void);
};

#endif