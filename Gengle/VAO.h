#pragma once	

#ifndef __OmniVAO__
#define __OmniVAO__

#include <GLEW/1.11.0/glew.h>  

class VAO
{
private:
	static const GLuint VAO::MAX_VAOS = 64;
	static GLuint VAO::current_index;
	static GLuint VAO::vao[VAO::MAX_VAOS];
	static GLboolean VAO::occupied[VAO::MAX_VAOS];
	GLint VAO::index;
public:
	GLboolean VAO::Activate(void);
	GLboolean VAO::Delete(void);
	GLboolean VAO::Initialize(void);
	GLboolean VAO::Valid(void);
	VAO::VAO();
	VAO::~VAO();
};

#endif // __OmniVAO__