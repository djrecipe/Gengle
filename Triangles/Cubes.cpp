#include "Cubes.h"
#include "GlobalTools.h"
#include "Shaders.h"

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

enum Attrib_IDs { attribVertices = 0, attribIndices = 1 };

static void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawElements(GL_TRIANGLES, Cubes::NumIndices, GL_UNSIGNED_INT, (void*)0);

    glFlush();
}

GLboolean Cubes::Start(void)
{
    this->vao.Initialize();
    // initialize shader(s)
    // TODO 09/14/16: embed resource files into application executable
    ShaderInfo shaders[] = {
        { GL_VERTEX_SHADER, "simple.vert" },
        { GL_FRAGMENT_SHADER, "simple.frag" },
        { GL_NONE, NULL } };

    GLuint program = Shaders::LoadShaders(shaders);
    glUseProgram(program);
    // vertices
    this->arrayBuffer.Initialize(BufferTypes::Array);
    GLfloat vertices[NumVertices][3] = {
        { -1.0f, -1.0f, -1.0f },
        { -1.0f, -1.0f,  1.0f },
        { -1.0f,  1.0f,  1.0f },
        {  1.0f,  1.0f,  1.0f },
        {  1.0f,  1.0f, -1.0f },
        {  1.0f, -1.0f, -1.0f },
        { -1.0f,  1.0f, -1.0f },
        {  1.0f, -1.0f,  1.0f } };
    this->arrayBuffer.SendData(vertices, sizeof(vertices));
    glVertexAttribPointer(attribVertices, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
    glEnableVertexAttribArray(attribVertices);
    // indices
    this->elementBuffer.Initialize(BufferTypes::Element);
    GLuint indices[NumIndices] = { 1, 2, 3, 7, 1, 3};
    this->elementBuffer.SendData(indices, sizeof(indices));
    //
    glPointSize(10.0f);
    this->vao.Activate();
    glutDisplayFunc(Display);
    glutMainLoop();

    return true;
}