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
	static const GLuint CubeGElement::NumVertices = 8;
	static const GLuint CubeGElement::NumIndices = 36;
	CubeGElement::CubeGElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void CubeGElement::Draw(void);
	void CubeGElement::Prepare(void);
};

#endif

