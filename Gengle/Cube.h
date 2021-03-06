#pragma once
#ifndef __OmniCube__
#define __OmniCube__

#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "VertexArray.h"
#include "Buffer.h"

class Cube : GElement
{
private:
public:
	static const GLuint Cube::NumVertices = 8;
	static const GLuint Cube::NumIndices = 36;
	Cube::Cube(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void Cube::Draw(void);
	void Cube::Prepare(void);
};

#endif

