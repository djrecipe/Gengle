#pragma once
#ifndef __OmniTriangle__
#define __OmniTriangle__

#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "VAO.h"
#include "Buffer.h"

class Triangle : GElement
{
private:
public:
	static const GLuint Triangle::NumVertices = 3;
	Triangle::Triangle(VAO* vao, Buffer* array_buffer_in);
	void Triangle::Draw(void);
	void Triangle::Prepare(void);
};

#endif

