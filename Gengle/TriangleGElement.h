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
	static const GLuint TriangleGElement::NumVertices = 3;
	TriangleGElement::TriangleGElement(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in);
	void TriangleGElement::Draw(void);
	void TriangleGElement::Prepare(void);
};

#endif

