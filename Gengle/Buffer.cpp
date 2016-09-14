#include "Buffer.h"

#pragma region Libraries
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma endregion

#pragma region Static Members
GLuint Buffer::buffer[Buffer::MAX_BUFFERS];
GLboolean Buffer::occupied[Buffer::MAX_BUFFERS] = {
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
Buffer::Buffer()
{
	this->index = -1;
    this->type = GL_ARRAY_BUFFER;
	return;
}
#pragma endregion

#pragma region Destruction
Buffer::~Buffer()
{
	if (this->Valid())
	{
		glDeleteBuffers(1, &Buffer::buffer[this->index]);
		Buffer::occupied[this->index] = false;
		this->index = -1;
	}
}
#pragma endregion

#pragma region Instance Methods	  
GLboolean Buffer::Activate(void)
{
    if (this->Valid())
    {
        glBindBuffer(this->type, Buffer::buffer[this->index]);
        return true;
    }
    return false;
}
GLboolean Buffer::Delete()
{
    if (this->Valid())
    {
        glBindBuffer(this->type, Buffer::buffer[this->index]);
        Buffer::occupied[this->index] = false;
        this->index = -1;
        return true;
    }
    return false;
}
GLboolean Buffer::Initialize(BufferTypes buffer_type)
{
    // remove old buffer
    this->Delete();
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
	GLint target_index = -1;
	for (GLint i = 0; i < Buffer::MAX_BUFFERS; i++)
	{
		if (!Buffer::occupied[i])
		{
			target_index = i;
			break;
		}
	}
	this->index = target_index;
	if (this->index > -1)
	{
		Buffer::occupied[this->index] = true;
		glGenBuffers(1, Buffer::buffer + this->index);
		return this->Activate();
	}
	return false;
}
GLboolean Buffer::SendData(const GLvoid* data, GLsizeiptr size)
{
	return this->SendData(data, size, GL_STATIC_DRAW);
}
GLboolean Buffer::SendData(const GLvoid* data, GLsizeiptr size, GLenum usage)
{
	if (this->Activate())
	{
		glBufferData(this->type, size, data, usage);
	}
	return true;
}
GLboolean Buffer::Valid(void)
{
	return this->index > -1;
}
#pragma endregion