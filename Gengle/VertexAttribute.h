#pragma once
#include <GLEW/1.11.0/glew.h>  

class VertexAttribute
{
private:
	GLuint index = 0;
	GLint size = -1;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	const void* pointer;
public:
	VertexAttribute::VertexAttribute(GLuint index_in, GLint size_in, GLenum type_in, GLboolean normalized_in, GLsizei stride_in, const void* pointer_in);
	void VertexAttribute::Prepare(void);
	void VertexAttribute::Disable(void);
	void VertexAttribute::Enable(void);
	VertexAttribute::~VertexAttribute();
};

