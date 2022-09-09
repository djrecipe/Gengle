#pragma once
#ifndef __OmniTriangle__
#define __OmniTriangle__

#include "GenericBuffer.h"
#include "GElement.h"
#include "GlobalTools.h"
#include "ShaderConfig.h"
#include "VertexArray.h"

/// <summary>
/// Basic axis
/// </summary>
class AxisGElement : public GElement
{
private:
public:
	static const GLuint NumVertices = 2;
	AxisGElement();
	AxisGElement(ShaderConfig* shaders, VertexArray* vao, GenericBuffer* array_buffer_in);
	void Draw(void);
	void Prepare(void);
};

#endif

