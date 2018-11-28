#include "Cube.h"
#include "GlobalTools.h"
#include "ShaderConfig.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

Cube::Cube(ShaderConfig shaders, VAO* vao, Buffer* array_buffer_in, Buffer* element_buffer_in) :
	GElement(shaders, vao, array_buffer_in, element_buffer_in)
{
	return;
}

void Cube::Draw(void)
{
	glDrawElements(GL_TRIANGLES, Cube::NumIndices, GL_UNSIGNED_INT, (void*)0);
	return;
}

void Cube::Prepare(void)
{
	// configure shaders
	this->shaders.Prepare();
	// activate vertex array object
	this->vao->Activate();
    // activate array buffer
	this->arrayBuffer->Activate();
	// send data to activated buffer
    GLfloat vertices[NumVertices][3] = {
        { -0.9f, -0.9f, -0.9f },
        { -0.9f, -0.9f,  0.9f },
        { -0.9f,  0.9f,  0.9f },
        {  0.9f,  0.9f,  0.9f },
        {  0.9f,  0.9f, -0.9f },
        {  0.9f, -0.9f, -0.9f },
        { -0.9f,  0.9f, -0.9f },
        {  0.9f, -0.9f,  0.9f } };
    this->arrayBuffer->SendData(vertices, sizeof(vertices));
    // activate element buffer
	this->elementBuffer->Activate();
	// send data to activated buffer
    GLuint indices[NumIndices] = { 1, 2, 3, 7, 1, 3};
    this->elementBuffer->SendData(indices, sizeof(indices));
    //
    glPointSize(10.0f);
    return;
}