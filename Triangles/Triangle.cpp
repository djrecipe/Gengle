#include "Triangle.h"
#include "GlobalTools.h"
#include "Shaders.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

enum Attrib_IDs { attribPosition = 0 };

static void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, Triangle::NumVertices);

	glFlush();
}

GLboolean Triangle::Start(void)
{
	this->vao.Initialize();
	this->buffer.Initialize(BufferTypes::Array);
	GLfloat vertices[NumVertices][3] = {
		{ -1.0f, -1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0f },
		{ -1.0f, 1.0f, 0.0f }};

	this->buffer.SendData(vertices, sizeof(vertices));
    // TODO 09/14/16: embed resource files into application executable
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "simple.vert" },
		{ GL_FRAGMENT_SHADER, "simple.frag" },
		{ GL_NONE, NULL } };

	GLuint program = Shaders::LoadShaders(shaders);
	glUseProgram(program);

	glVertexAttribPointer(attribPosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(attribPosition);
	glPointSize(10.0f);
	this->vao.Activate();
	glutDisplayFunc(Display);
	glutMainLoop();

	return true;
}