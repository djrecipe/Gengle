#include "GengleEngine.h"

#include "CubeGElement.h"
#include "TriangleGElement.h"
#include "VoxelCubeArrayGElement.h"

#include <GLEW/1.11.0/glew.h>
#include <Freeglut/2.8.1/VS2013/freeglut.h>	

GengleEngine* GengleEngine::instance = NULL;

void GengleEngine::DrawCallback()
{
	for (GElement* element : GengleEngine::instance->elements)
	{
		element->Prepare();
		element->Draw();
	}
	//GengleEngine::instance->ProcessPhysics();
	//GengleEngine::instance->inputTransmitter->TransmitViewUpdate();
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
		break;
	}
	return;
}

void GengleEngine::MouseCallback(int x, int y)
{
	GengleEngine::instance->inputReceiver->ProcessMouseMovement(x, y);
	return;
}

void GengleEngine::MouseButtonCallback(int button, int state, int x, int y)
{
	//switch (button)
	//{
	//case GLUT_LEFT_BUTTON:
	//	switch (state)
	//	{
	//	case GLUT_DOWN:
	//		GElement* entity = GengleEngine::instance->AddBasicElement(CubeElement);
	//		glm::vec3 direction = glm::normalize(GengleEngine::instance->inputUpdate->GetViewDirection());
	//		glm::vec2 angles = GengleEngine::instance->inputUpdate->GetViewAngles();
	//		direction *= 10.0;
	//		entity->SetVelocity(direction);
	//		entity->SetRotation(glm::radians(-1.0*angles[0]), glm::vec3(0.0, 1.0, 0.0));
	//		entity->SetRotation(glm::radians(angles[1]), glm::vec3(0.0, 0.0, 1.0), RotationOrderTwo);
	//		break;
	//	}
	//	break;
	//}
	//return;
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

GengleEngine::GengleEngine()
{
	this->window_size = glm::vec2(1600, 900);
	// create mouse input manager
	this->inputUpdate = new InputUpdate();
	this->inputReceiver = new InputReceiver(inputUpdate, this->window_size);
	// create vao
	this->vao = new VertexArray();
	this->vao->Initialize();
	// create buffers
	this->arrayBuffer = new GenericBuffer();
	this->arrayBuffer->Initialize(BufferTypes::Array);
	this->elementBuffer = new GenericBuffer();
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
		GengleEngine::SpecialKeyboardCallback, GengleEngine::MouseCallback,
		GengleEngine::MouseButtonCallback))
		throw std::runtime_error("Error while initializing Glut");
	// create vao
	this->vao = new VertexArray();
	this->vao->Initialize();
	// create buffers
	this->arrayBuffer = new GenericBuffer();
	this->arrayBuffer->Initialize(BufferTypes::Array);
	this->elementBuffer = new GenericBuffer();
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

GElement* GengleEngine::AddBasicElement(GElement* element, SpawnOriginTypes origin_type, glm::vec3 origin)
{
	element->Initialize(this->shaderConfig, this->vao, this->arrayBuffer, this->elementBuffer);
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
void GengleEngine::DrawIteration()
{
	this->DrawCallback();
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

void GengleEngine::StartWithGlut(void)
{
	// enable shader
	this->shaderConfig->Prepare();
	// send projection matrix
	glm::mat4 initial_projection_matrix = glm::perspective(glm::radians(45.0f), window_size[0] / window_size[1], 0.1f, 10000.0f);
	this->shaderConfig->GetUniform("projectionMatrix")->SetValue(initial_projection_matrix);
	// send view matrix
	glm::mat4 initial_view_matrix = glm::mat4(1.0);
	this->shaderConfig->GetUniform("viewMatrix")->SetValue(initial_view_matrix);
	// start engine
	GlutManager::Start();
	return;
}
void GengleEngine::StartWithoutGlut(void)
{
	// enable shader
	this->shaderConfig->Prepare();
	// send projection matrix
	glm::mat4 initial_projection_matrix = glm::perspective(glm::radians(45.0f), window_size[0] / window_size[1], 0.1f, 10000.0f);
	this->shaderConfig->GetUniform("projectionMatrix")->SetValue(initial_projection_matrix);
	// send view matrix
	glm::mat4 initial_view_matrix = glm::mat4(1.0);
	this->shaderConfig->GetUniform("viewMatrix")->SetValue(initial_view_matrix);
	return;
}
