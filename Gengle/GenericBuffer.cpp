#include "GenericBuffer.h"
#include <assert.h> 

#include "ShaderConfig.h"

#pragma region Libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma endregion

#pragma region Static Members
GLuint GenericBuffer::current_index = 0;
GLuint GenericBuffer::buffer[GenericBuffer::MAX_BUFFERS];
GLboolean GenericBuffer::occupied[GenericBuffer::MAX_BUFFERS] = {
false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false,
false, false, false, false, false, false, false, false };
#pragma endregion

#pragma region Constructors
GenericBuffer::GenericBuffer()
{
	this->index = -1;
    this->type = GL_ARRAY_BUFFER;
	return;
}
#pragma endregion

#pragma region Destruction
GenericBuffer::~GenericBuffer()
{
	this->Delete();
	return;
}
#pragma endregion

#pragma region Instance Methods	  
GLboolean GenericBuffer::Activate(void)
{
    if (this->Valid())
    {
        glBindBuffer(this->type, GenericBuffer::buffer[this->index]);
        return true;
    }
    return false;
}
GLboolean GenericBuffer::Delete()
{
    if (this->Valid())
    {
        glBindBuffer(this->type, GenericBuffer::buffer[this->index]);
		glDeleteBuffers(1, &GenericBuffer::buffer[this->index]);
        GenericBuffer::occupied[this->index] = false;
        this->index = -1;
        return true;
    }
    return false;
}
GLboolean GenericBuffer::Initialize(BufferTypes buffer_type)
{
	// assert uninitialized
	assert(!this->Valid());
    // assign buffer style
    switch (buffer_type)
    {
        default:
        case Array:
            this->type = GL_ARRAY_BUFFER;
            break;
        case Element:
            this->type = GL_ELEMENT_ARRAY_BUFFER;
            break;
    }
	// find unoccupied index
	GLint target_index = -1;
	for (GLint i = GenericBuffer::current_index; i < GenericBuffer::MAX_BUFFERS; i++)
	{
		if (!GenericBuffer::occupied[i])
		{
			target_index = i;
			break;
		}
	}
	if (target_index < 0)
	{
		for (GLint i = 0; i < GenericBuffer::current_index; i++)
		{
			if (!GenericBuffer::occupied[i])
			{
				target_index = i;
				break;
			}
		}
	}
	this->index = target_index;
	// assign buffer
	if (this->index > -1)
	{
		GenericBuffer::occupied[this->index] = true;
		glGenBuffers(1, GenericBuffer::buffer + this->index);
		return true;
	}
	return false;
}
GLboolean GenericBuffer::SendData(const GLvoid* data, GLsizeiptr size)
{
	return this->SendData(data, size, GL_DYNAMIC_DRAW);
}
GLboolean GenericBuffer::SendData(const GLvoid* data, GLsizeiptr size, GLenum usage)
{
	if (this->Activate())
	{
		glBufferData(this->type, size, data, usage);
	}
	return true;
}
GLboolean GenericBuffer::Valid(void)
{
	return this->index > -1;
}
#pragma endregion