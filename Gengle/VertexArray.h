#pragma once	

#ifndef __OmniVertexArray__
#define __OmniVertexArray__

#include "GlobalTools.h"

/// <summary>
/// Vertex array descriptor and function wrapper
/// </summary>
class VertexArray
{
private:
	static const GLuint VertexArray::MAX_VAOS = 64;
	static GLuint VertexArray::current_index;
	static GLuint VertexArray::vao[VertexArray::MAX_VAOS];
	static GLboolean VertexArray::occupied[VertexArray::MAX_VAOS];
	GLint VertexArray::index;
public:
	void VertexArray::Activate(void);
	void VertexArray::Delete(void);
	void VertexArray::Initialize(void);
	GLboolean VertexArray::Valid(void);
	VertexArray::VertexArray();
	VertexArray::~VertexArray();
};

#endif // __OmniVertexArray__