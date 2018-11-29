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
	// create shader descriptor(s)
	ShaderInfo shader_infos[] = {
		{ GL_VERTEX_SHADER, "simple.vert" },
		{ GL_FRAGMENT_SHADER, "simple.frag" },
		{ GL_NONE, NULL } };
	std::vector<VertexAttribute> attributes;
	VertexAttribute attribute(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	attributes.push_back(attribute);
	std::vector<ShaderUniform> uniforms;
	ShaderUniform model_view_matrix_uniform("modelMatrix", GL_MATRIX4_ARB);
	ShaderUniform projection_matrix_uniform("projectionViewMatrix", GL_MATRIX4_ARB);
	uniforms.push_back(model_view_matrix_uniform);
	uniforms.push_back(projection_matrix_uniform);
	ShaderConfig shader_info(shader_infos, attributes, uniforms);
	// create elements
	GElement * element = (GElement*)new Triangle(shader_info, vao, array_buffer);
	elements.push_back(element);
	element = (GElement*)new Cube(shader_info, vao, array_buffer, element_buffer);
	element->SetScale(glm::vec3(0.5, 0.5, 0.5));
	element->SetRotation(0.1f, glm::vec3(1.0, 0.0, 0.0));
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
