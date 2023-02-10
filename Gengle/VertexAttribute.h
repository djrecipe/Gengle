#pragma once

#ifndef __OmniVertexAttribute__
#define __OmniVertexAttribute__

#include "GlobalTools.h"

/// <summary>
/// Vertex attribute array descriptor and function wrapper
/// </summary>
class VertexAttribute
{
private:
	const GLchar* name;
	GLuint index = 0;
	GLint size = -1;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	const void* pointer;
public:
	VertexAttribute(const GLchar* name_in, GLuint index_in, GLint size_in, GLenum type_in,
		GLboolean normalized_in, GLsizei stride_in, const void* pointer_in);
	const GLchar* GetName(void) { return name; }
	void Prepare(void);
	void Disable(void);
	void Enable(void);
	~VertexAttribute();
};

#endif // __OmniVertexAttribute__