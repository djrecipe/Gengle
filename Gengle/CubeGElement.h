#pragma once
#ifndef __OmniCube__
#define __OmniCube__

#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "VertexArray.h"
#include "Buffer.h"

class CubeGElement : public GElement
{
private:
public:
	static const GLuint NumVertices = 8;
	static const GLuint NumIndices = 36;
	CubeGElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void Draw(void);
	void Prepare(void);
};

#endif

