#pragma once

#ifndef __OmniBuffer__
#define __OmniBuffer__

#include <GLEW/1.11.0/glew.h>  

enum BufferTypes { Array = 0, Element = 1, TexCoord = 2 };

class GenericBuffer
{
private:
	static const GLuint MAX_BUFFERS = 64;
	static GLuint current_index;
	static GLuint buffer[GenericBuffer::MAX_BUFFERS];
	static GLboolean occupied[GenericBuffer::MAX_BUFFERS];
	GLint index;
	GLenum type;
public:
	GLboolean Activate(void);
    GLboolean Delete(void);
	GLboolean Initialize(BufferTypes buffer_type);
	GLboolean SendData(const GLvoid* data, GLsizeiptr size);
	GLboolean SendData(const GLvoid* data, GLsizeiptr size, GLenum usage);
	GLboolean Valid(void);
	GenericBuffer();
	~GenericBuffer();
};

#endif // __OmniBuffer__

