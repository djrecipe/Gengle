#include "Gengle.pch.h"
#include "VertexAttribute.h"

#pragma region Instance Methods
/// <summary>
/// Create a new vertex attribute using the specified parameters
/// </summary>
/// <seealso cref="glVertexAttribPointer"/>
/// <param name="index_in">Vertex attribute index (identifier)</param>
/// <param name="size_in">Number of components per vertex attribute (1-4)</param>
/// <param name="type_in">Data type of each component</param>
/// <param name="normalized_in">Determines whether values should be normalized</param>
/// <param name="stride_in">Byte offset between consecutive attribute values</param>
/// <param name="pointer_in">Pointer offset to the first vertex attribute component</param>
VertexAttribute::VertexAttribute(const GLchar* name_in, GLuint index_in, GLint size_in, GLenum type_in,
	GLboolean normalized_in, GLsizei stride_in, const void* pointer_in)
{
	this->name = name_in;
	this->index = index_in;
	this->size = size_in;
	this->type = type_in;
	this->normalized = normalized_in;
	this->stride = stride_in;
	this->pointer = pointer_in;
	return;
}

/// <summary>
/// Destroy the VertexAttribute instance
/// </summary>
VertexAttribute::~VertexAttribute()
{
	return;
}

/// <summary>
/// Disable the vertex attribute array
/// </summary>
/// <seealso cref="glDisableVertexAttribArray"/>
void VertexAttribute::Disable(void)
{
	//dprint("Disabling vertex attribute # %d", this->index);
	glDisableVertexAttribArray(this->index);
	return;
}

/// <summary>
/// Enable the vertex attribute array
/// </summary>
/// <seealso cref="glEnableVertexAttribArray"/>
void VertexAttribute::Enable(void)
{
	//dprint("Enabling vertex attribute # %d", this->index);
	glEnableVertexAttribArray(this->index);
	return;
}

/// <summary>
/// Prepare the vertex attribute array for usage
/// </summary>
/// <seealso cref="glVertexAttribPointer"/>
void VertexAttribute::Prepare(void)
{
	//dprint("VERTEX ATTRIBUTE ::: Index: %d | Size: %d", this->index, this->size);
	glVertexAttribPointer(this->index, this->size, this->type, this->normalized, this->stride, this->pointer);
	return;
}
#pragma endregion

