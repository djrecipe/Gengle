#include "Gengle.pch.h"
#include "VertexArray.h"	

#pragma region Static Members
GLuint VertexArray::current_index = 0;
GLuint VertexArray::vao[VertexArray::MAX_VAOS];
GLboolean VertexArray::occupied[VertexArray::MAX_VAOS] = { false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false,
													false, false, false, false, false, false, false, false };
#pragma endregion

#pragma region Instance Methods
/// <summary>
/// Create a new, default vertex array descriptor
/// </summary>
VertexArray::VertexArray(void)
{
	this->index = -1;
	return;
}

/// <summary>
/// Destroy the vertex array object and free the index
/// </summary>
VertexArray::~VertexArray(void)
{
	this->Delete();
	return;
}

/// <summary>
/// Activate/bind the vertex array
/// </summary>
/// <seealso cref="glBindVertexArray"/>
void VertexArray::Activate(void)
{
	assert(this->Valid());
	glBindVertexArray(VertexArray::vao[this->index]);
	return;
}

/// <summary>
/// Delete and free the vertex array
/// </summary>
/// <seealso cref="glDeleteVertexArrays"/>
void VertexArray::Delete(void)
{
	assert(this->Valid());
	glBindVertexArray(VertexArray::vao[this->index]);
	glDeleteVertexArrays(1, &VertexArray::vao[this->index]);
	VertexArray::occupied[this->index] = false;
	this->index = -1;
	return;
}

/// <summary>
/// Generate a vertex array object via OpenGL and reserve an index
/// </summary>
/// <seealso cref="glGenVertexArrays"/>
void VertexArray::Initialize(void)
{
	// assert uninitialized
	assert(!this->Valid());
	// find unoccupied index
	GLint target_index = -1;
	for (GLint i = VertexArray::current_index; i < VertexArray::MAX_VAOS; i++)
	{
		if (!VertexArray::occupied[i])
		{
			target_index = i;
			break;
		}
	}
	if (target_index < 0)
	{
		for (GLint i = 0; i < VertexArray::current_index; i++)
		{
			if (!VertexArray::occupied[i])
			{
				target_index = i;
				break;
			}
		}
	}
	// assign and validate index
	this->index = target_index;
	if (this->index <= -1)
		throw new std::runtime_error("Error while initializing vertex array");
	// assign vao
	VertexArray::current_index = this->index;
	VertexArray::occupied[VertexArray::current_index] = true;
	glGenVertexArrays(1, VertexArray::vao + this->index);
	this->Activate();
	return;
}

/// <summary>
/// Determine if the vertex array is valid
/// </summary>
/// <remarks>Vertex array is valid if the assigned index is greater than -1</remarks>
/// <returns>True if the vertex array is valid, False otherwise</returns>
GLboolean VertexArray::Valid(void)
{
	return this->index > -1;
}
#pragma endregion
