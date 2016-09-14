#pragma once
#ifndef __OmniTriangles__
#define __OmniTriangles

#include <GLEW/1.11.0/glew.h> 
#include "VAO.h"
#include "Buffer.h"

class Triangles
{
private:
	VAO Triangles::vao;
	Buffer Triangles::buffer;
public:
	static const GLuint Triangles::NumVertices = 6;
	GLboolean Triangles::Start(void);
};

#endif

