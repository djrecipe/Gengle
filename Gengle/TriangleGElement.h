#pragma once
#ifndef __OmniTriangle__
#define __OmniTriangle__

#include "GenericBuffer.h"
#include "GElement.h"
#include "ShaderConfig.h"
#include "VertexArray.h"

/// <summary>
/// Basic triangle
/// </summary>
class TriangleGElement : GElement
{
private:
public:
	static const GLuint NumVertices = 3;
	TriangleGElement(ShaderConfig* shaders, VertexArray* vao, GenericBuffer* array_buffer_in);
	void Draw(void);
	void Prepare(void);
	void PrepareTexture(void);
};

#endif

