#pragma once
#ifndef __OmniSphere__
#define __OmniSphere__

#include <GLEW/1.11.0/glew.h> 
#include "GElement.h"
#include "GlobalTools.h"
#include "VertexArray.h"
#include "Buffer.h"

class Sphere : GElement
{
private:
	GLuint Sphere::stackCount = 4;
	GLuint Sphere::sectorCount = 4;
	GLuint Sphere::numVertices = 5;
	GLuint Sphere::numIndices = 18;
	GLuint * Sphere::indices = NULL;
	GLfloat ** Sphere::vertices = NULL;
public:
	
	Sphere::Sphere(ShaderConfig* shaders, VertexArray* vao, Buffer* array_buffer_in, Buffer* element_buffer_in);
	void Sphere::Draw(void);
	void Sphere::Prepare(void);
	void Sphere::GenerateVertices(void);
};

#endif