#include "Triangles.h"
#include "GlobalTools.h"
#include "Shaders.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

enum Attrib_IDs { attribPosition = 0 };

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glDrawArrays(GL_TRIANGLES, 0, Triangles::NumVertices);

	glFlush();
}

GLboolean Triangles::Start(void)
{
	this->vao.Initialize();
	this->buffer.Initialize(GL_ARRAY_BUFFER);
	GLfloat vertices[NumVertices][2] = {
		{ -0.90f, -0.90f },
		{ 0.85f, -0.90f },
		{ -0.90f, 0.85f },
		{ 0.90f, -0.85f },
		{ 0.90f, 0.90f },
		{ -0.85f, 0.90f } };

	this->buffer.SendData(vertices, sizeof(vertices));

	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL } };

	GLuint program = Shaders::LoadShaders(shaders);
	glUseProgram(program);

	glVertexAttribPointer(attribPosition, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(attribPosition);
	glPointSize(10.0f);
	this->vao.Activate();
	glutDisplayFunc(Display);
	glutMainLoop();

	return true;
}