#pragma once
#ifndef __OmniTriangle__
#define __OmniTriangle__

#include "Buffer.h"
#include "GElement.h"
#include "GlobalTools.h"
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
	TriangleGElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in);
	void Draw(void);
	void Prepare(void);
};

#endif

