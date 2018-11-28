#include "VertexAttribute.h"

#include "GlobalTools.h"

VertexAttribute::VertexAttribute(GLuint index_in, GLint size_in, GLenum type_in,
	GLboolean normalized_in, GLsizei stride_in, const void* pointer_in)
{
	this->index = index_in;
	this->size = size_in;
	this->type = type_in;
	this->normalized = normalized_in;
	this->stride = stride_in;
	this->pointer = pointer_in;
	return;
}

void VertexAttribute::Disable(void)
{
	//dprint("Disabling vertex attribute # %d", this->index);
	glDisableVertexAttribArray(this->index);
	return;
}

void VertexAttribute::Enable(void)
{
	//dprint("Enabling vertex attribute # %d", this->index);
	glEnableVertexAttribArray(this->index);
	return;
}

void VertexAttribute::Prepare(void)
{
	//dprint("VERTEX ATTRIBUTE ::: Index: %d | Size: %d", this->index, this->size);
	glVertexAttribPointer(this->index, this->size, this->type, this->normalized, this->stride, this->pointer);
	return;
}

VertexAttribute::~VertexAttribute()
{
	return;
}
