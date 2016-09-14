#pragma once

#ifndef __OmniBuffer__
#define __OmniBuffer__

#include <GLEW/1.11.0/glew.h>  

class Buffer
{
private:
	static const GLuint Buffer::MAX_BUFFERS = 64;
	static GLuint Buffer::current_index;
	static GLuint Buffer::buffer[Buffer::MAX_BUFFERS];
	static GLboolean Buffer::occupied[Buffer::MAX_BUFFERS];
	GLint Buffer::index;
	GLenum Buffer::type;
public:
	GLboolean Buffer::Activate(void);
	GLboolean Buffer::Initialize(GLenum target);
	GLboolean Buffer::SendData(const GLvoid* data, GLsizeiptr size);
	GLboolean Buffer::SendData(const GLvoid* data, GLsizeiptr size, GLenum usage);
	GLboolean Buffer::Valid(void);
	Buffer::Buffer();
	Buffer::~Buffer();
};

#endif // __OmniBuffer__

