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
class Triangle : GElement
{
private:
public:
	static const GLuint Triangle::NumVertices = 3;
	Triangle::Triangle(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void Triangle::Draw(void);
	void Triangle::Prepare(void);
};

#endif

