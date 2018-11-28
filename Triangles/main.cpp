#include <iostream>
#include <vector>
using namespace std;

#define FREEGLUT_STATIC

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <GLEW/1.11.0/glew.h>
#include <Freeglut/2.8.1/VS2013/freeglut.h>	

#include "GlobalTools.h"    
#include "Cube.h"
#include "Triangle.h"
#include "GlutManager.h"

static std::vector<GElement*> elements;

static void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (GElement* element : elements)
	{
		element->Prepare();
		element->Draw();
	}

	glFlush();
}

void KeyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{

	}
}
void SpecialKeyboardCallback(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
}

int main(int argc, char** argv)
{
	if (!GlutManager::Initialize(argc, argv, KeyboardCallback, SpecialKeyboardCallback))
		return -1;
	// create vao
	VAO* vao = new VAO();
	vao->Initialize();
	// create buffers
	Buffer* array_buffer = new Buffer();
	array_buffer->Initialize(BufferTypes::Array);
	Buffer* element_buffer = new Buffer();
	element_buffer->Initialize(BufferTypes::Element);
	// create elements
	GElement * element = (GElement*)new Triangle(vao, array_buffer);
	elements.push_back(element);
	element = (GElement*)new Cube(vao, array_buffer, element_buffer);
	elements.push_back(element);
	// start display loop
	glutDisplayFunc(Draw);
	glutMainLoop();
	// delete element pointers
	for (GElement* element : elements)
	{
		delete element;
	}
	return 0;
}
