#include "GengleEngine.h"

#include "Cube.h"
#include "Triangle.h"

#include <GLEW/1.11.0/glew.h>
#include <Freeglut/2.8.1/VS2013/freeglut.h>	

GengleEngine* GengleEngine::instance = NULL;

void GengleEngine::DrawCallback()
{
	glClear(GL_COLOR_BUFFER_BIT);

	for (GElement* element : GengleEngine::instance->elements)
	{
		element->Prepare();
		element->Draw();
	}

	glFlush();
	GengleEngine::instance->ProcessPhysics();
	GengleEngine::instance->inputTransmitter->TransmitViewUpdate();
	return;
}

void GengleEngine::IdleCallback()
{
	GengleEngine::instance->ProcessPhysics();
	GengleEngine::instance->inputTransmitter->TransmitViewUpdate();
	return;
}

void GengleEngine::KeyboardCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveForward, KeyStateDown);
		break;
	case 's':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveBackward, KeyStateDown);
		break;
	case 'a':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveLeft, KeyStateDown);
		break;
	case 'd':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveRight, KeyStateDown);
		break;
	case 'r':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveUp, KeyStateDown);
		break;
	case 'f':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveDown, KeyStateDown);
		break;
	case 27:
		GlutManager::Exit();
		exit(0);
		break;
	}
	return;
}

void GengleEngine::KeyboardUpCallback(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveForward, KeyStateUp);
		break;
	case 's':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveBackward, KeyStateUp);
		break;
	case 'a':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveLeft, KeyStateUp);
		break;
	case 'd':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveRight, KeyStateUp);
		break;
	case 'r':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveUp, KeyStateUp);
		break;
	case 'f':
		GengleEngine::instance->inputReceiver->ProcessKeyboardEvent(MoveDown, KeyStateUp);
		break;
	case 'x':
		GElement* entity = GengleEngine::instance->AddBasicElement(CubeElement);
		entity->SetVelocity(glm::vec3(0.1, 0.0, 0.0));
		break;
	}
	return;
}

void GengleEngine::MouseCallback(int x, int y)
{
	GengleEngine::instance->inputReceiver->ProcessMouseMovement(x, y);
	return;
}

void GengleEngine::SpecialKeyboardCallback(int key, int x, int y)
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

GengleEngine::GengleEngine(GLint argc, GLchar** argv, glm::vec2 window_size_in)
{
	this->window_size = window_size_in;
	// create mouse input manager
	this->inputUpdate = new InputUpdate();
	this->inputReceiver = new InputReceiver(inputUpdate, this->window_size);
	// initialize glut manager
	if (!GlutManager::Initialize(argc, argv, this->window_size,
		GengleEngine::DrawCallback, GengleEngine::IdleCallback,
		GengleEngine::KeyboardCallback, GengleEngine::KeyboardUpCallback,
		GengleEngine::SpecialKeyboardCallback, GengleEngine::MouseCallback))
		throw std::runtime_error("Error while initializing Glut");
	// create vao
	this->vao = new VertexArray();
	this->vao->Initialize();
	// create buffers
	this->arrayBuffer = new Buffer();
	this->arrayBuffer->Initialize(BufferTypes::Array);
	this->elementBuffer = new Buffer();
	this->elementBuffer->Initialize(BufferTypes::Element);
	// define vertex attribute arrays
	std::vector<VertexAttribute> attributes;
	VertexAttribute attribute(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	attributes.push_back(attribute);
	// create shader configuration
	ShaderInfo shader_infos[] = {
		{ GL_VERTEX_SHADER, "simple.vert" },
		{ GL_FRAGMENT_SHADER, "simple.frag" },
		{ GL_NONE, NULL } };
	this->shaderConfig = new ShaderConfig(shader_infos, attributes);
	this->shaderConfig->AddUniform("modelMatrix");
	this->shaderConfig->AddUniform("projectionMatrix");
	this->shaderConfig->AddUniform("viewMatrix");
	// create input transmitter
	this->inputTransmitter = new InputTransmitter(inputUpdate,
		this->shaderConfig->GetUniform("projectionMatrix"),
		this->shaderConfig->GetUniform("viewMatrix"));
	// create physics engine
	this->physicsEngine = new PhysicsEngine();
	// set instance
	GengleEngine::instance = this;
	return;
}


GengleEngine::~GengleEngine()
{
	GlutManager::Exit();

	delete this->physicsEngine;

	delete this->shaderConfig;
	delete this->vao;
	delete this->arrayBuffer;
	delete this->elementBuffer;

	delete this->inputTransmitter;
	delete this->inputReceiver;
	delete this->inputUpdate;

	for (GElement* element : this->elements)
		delete element;

	GengleEngine::instance = NULL;
	return;
}

GElement* GengleEngine::AddBasicElement(BasicElementTypes type, SpawnOriginTypes origin_type, glm::vec3 origin)
{

	GElement * element = NULL;
	switch (type)
	{
	case TriangleElement:
		element = (GElement*)new Triangle(this->shaderConfig, this->vao, this->arrayBuffer);
		break;
	case CubeElement:
		element = (GElement*)new Cube(this->shaderConfig, this->vao,
			this->arrayBuffer, this->elementBuffer);
		break;
	}
	switch (origin_type)
	{
	case AbsoluteSpawnOrigin:
		element->SetOrigin(origin);
		break;
	case RelativeSpawnOrigin:
		element->SetOrigin(this->inputUpdate->GetViewTranslations() + origin);
		break;
	}
	this->elements.push_back(element);
	return element;
}

void GengleEngine::ProcessPhysics(void)
{
	// retrieve physics results
	std::map<GUID, PhysicsDescriptor, GUIDComparer> results = this->physicsEngine->GetOutputs();
	// loop through entities
	std::map<GUID, PhysicsDescriptor, GUIDComparer> inputs;
	std::map<GUID, PhysicsDescriptor, GUIDComparer>::iterator iterator;
	for (GElement* element : this->elements)
	{
		if (!element->GetEnablePhysics())
			continue;
		iterator = results.find(element->GetID());
		if (iterator != results.end())
			element->ConsumePhysicsDescriptor(iterator->second);
		PhysicsDescriptor physics = element->GetPhysicsDescriptor();
		inputs.insert(std::make_pair(element->GetID(), physics));
	}
	// send new physics entity properties to physics engine
	this->physicsEngine->SetInputs(inputs);
	return;
}

void GengleEngine::Start(void)
{
	// enable shader
	this->shaderConfig->Prepare();
	// send projection matrix
	glm::mat4 initial_projection_matrix = glm::perspective(glm::radians(45.0f), window_size[0] / window_size[1], 0.1f, 1000.0f);
	this->shaderConfig->GetUniform("projectionMatrix")->SetValue(initial_projection_matrix);
	// send view matrix
	glm::mat4 initial_view_matrix = glm::mat4(1.0);
	this->shaderConfig->GetUniform("viewMatrix")->SetValue(initial_view_matrix);
	// start engine
	GlutManager::Start();
	return;
}
