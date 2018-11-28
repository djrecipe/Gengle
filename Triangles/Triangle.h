#pragma once
#ifndef __OmniTriangles__
#define __OmniTriangles__

#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "VAO.h"
#include "Buffer.h"

class Triangle : GElement
{
private:
	VAO Triangle::vao;
	Buffer Triangle::buffer;
public:
	static const GLuint Triangle::NumVertices = 3;
	GLboolean Triangle::Start(void);
};

#endif

