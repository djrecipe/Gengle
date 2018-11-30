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
#include "InputReceiver.h"
#include "InputTransmitter.h"

static std::vector<GElement*> elements;
static InputReceiver * inputReceiver;
static InputUpdate * inputUpdate;
static InputTransmitter * inputTransmitter;

static void DrawCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (GElement* element : elements)
	{
		element->Prepare();
		element->Draw();
	}

	glFlush();
	inputTransmitter->TransmitViewUpdate();
}

static void IdleCallback()
{
	inputTransmitter->TransmitViewUpdate();
}

void KeyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		inputReceiver->ProcessMovementCommand(MoveForward);
		break;
	case 's':
		inputReceiver->ProcessMovementCommand(MoveBackward);
		break;
	case 'a':
		inputReceiver->ProcessMovementCommand(MoveLeft);
		break;
	case 'd':
		inputReceiver->ProcessMovementCommand(MoveRight);
		break;
	case 'r':
		inputReceiver->ProcessMovementCommand(MoveUp);
		break;
	case 'f':
		inputReceiver->ProcessMovementCommand(MoveDown);
		break;
	case 27:
		GlutManager::Exit();
		exit(0);
		break;
	}
}

void MouseCallback(int x, int y)
{
	inputReceiver->ProcessMouseMovement(x, y);
	return;
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
	glm::vec2 window_size = glm::vec2(512, 512);
	// create mouse input manager
	inputUpdate = new InputUpdate();
	inputReceiver = new InputReceiver(inputUpdate, window_size);
	// initialize glut manager
	if (!GlutManager::Initialize(argc, argv, window_size,DrawCallback,IdleCallback,
		KeyboardCallback, SpecialKeyboardCallback, MouseCallback))
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
	std::vector<ShaderUniform*> uniforms;
	ShaderUniform * model_matrix_uniform = new ShaderUniform("modelMatrix");
	ShaderUniform * projection_matrix_uniform = new ShaderUniform("projectionMatrix");
	ShaderUniform * view_matrix_uniform = new ShaderUniform("viewMatrix");
	uniforms.push_back(model_matrix_uniform);
	uniforms.push_back(projection_matrix_uniform);
	uniforms.push_back(view_matrix_uniform);
	ShaderConfig shader_info(shader_infos, attributes, uniforms);
	// create input transmitter
	glm::mat4 initial_view_matrix = glm::mat4(1.0);
	view_matrix_uniform->SetValue(initial_view_matrix);
	inputTransmitter = new InputTransmitter(inputUpdate, projection_matrix_uniform, view_matrix_uniform);
	// create elements
	GElement * element = (GElement*)new Triangle(shader_info, vao, array_buffer);
	elements.push_back(element);
	element = (GElement*)new Cube(shader_info, vao, array_buffer, element_buffer);
	element->SetScale(glm::vec3(20.0, 20.0, 20.0));
	element->SetRotation(glm::radians(0.0f), glm::vec3(1.0, 0.0, 0.0));
	element->SetOrigin(glm::vec3(30.0, 30.0, 30.0));
	elements.push_back(element);
	// send projection matrix
	shader_info.Prepare();
	glm::mat4 initial_projection_matrix = glm::perspective(glm::radians(45.0f), window_size[0] / window_size[1], 0.1f, 1000.0f);
	projection_matrix_uniform->SetValue(initial_projection_matrix);
	// start display loop
	GlutManager::Start();
	// delete element pointers
	for (GElement* element : elements)
	{
		delete element;
	}
	// delete shader uniforms
	for (ShaderUniform * uniform : uniforms)
	{
		delete uniform;
	}
	delete inputTransmitter;
	delete inputReceiver;
	delete inputUpdate;
	return 0;
}
