#include "Cube.h"
#include "GlobalTools.h"
#include "Shaders.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

enum Attrib_IDs { attribVertices = 0 };

Cube::Cube(VAO* vao, Buffer* array_buffer_in, Buffer* element_buffer_in) : GElement(vao, array_buffer_in, element_buffer_in)
{

}

void Cube::Draw(void)
{
	glDrawElements(GL_TRIANGLES, Cube::NumIndices, GL_UNSIGNED_INT, (void*)0);
	return;
}

void Cube::Prepare(void)
{
	this->vao->Activate();
    // initialize shader(s)
    // TODO 09/14/16: embed resource files into application executable
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "simple.vert" },
        { GL_FRAGMENT_SHADER, "simple.frag" },
        { GL_NONE, NULL } };

    GLuint program = Shaders::LoadShaders(shaders);
    glUseProgram(program);
    // vertices
	this->arrayBuffer->Activate();
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
    glEnableVertexAttribArray(attribVertices);
    glVertexAttribPointer(attribVertices, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    // indices
	this->elementBuffer->Activate();
    GLuint indices[NumIndices] = { 1, 2, 3, 7, 1, 3};
    this->elementBuffer->SendData(indices, sizeof(indices));
    //
    glPointSize(10.0f);
    this->vao->Activate();

    return;
}