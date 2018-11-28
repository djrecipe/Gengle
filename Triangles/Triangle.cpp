#include "Triangle.h"
#include "GlobalTools.h"
#include "ShaderConfig.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

Triangle::Triangle(ShaderConfig shaders, VAO* vao, Buffer* array_buffer_in) : GElement(shaders, vao, array_buffer_in)
{
	return;
}

void Triangle::Draw(void)
{
	glDrawArrays(GL_TRIANGLES, 0, Triangle::NumVertices);
	return;
}

void Triangle::Prepare(void)
{
	// configure shaders
	this->shaders.Prepare();
	// send uniform values
	ShaderUniform temp = this->shaders.GetUniform("modelViewMatrix");
	glm::mat4x4 matrix(1.0);
	temp.SetValue(matrix);
	temp = this->shaders.GetUniform("projectionMatrix");
	temp.SetValue(matrix);
	// activate vertex array object
	this->vao->Activate();
	// activate array buffer
	this->arrayBuffer->Activate();
	// send data to activated buffer
	GLfloat vertices[NumVertices][3] = {
		{ -1.0f, -1.0f, 0.0f },
		{ 1.0f, -1.0f, 0.0f },
		{ -1.0f, 1.0f, 0.0f }};
	this->arrayBuffer->SendData(vertices, sizeof(vertices));
	//
	glPointSize(10.0f);
	return;
}