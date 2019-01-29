#pragma once
#include "VertexArray.h"
#include "GElement.h"
#include "GlutManager.h"
#include "InputReceiver.h"
#include "InputTransmitter.h"
#include "InputUpdate.h"
#include "PhysicsEngine.h"

enum BasicElementTypes : GLuint { TriangleElement = 0, CubeElement = 1};

class GengleEngine
{
private:
	static GengleEngine* instance;

	static void GengleEngine::DrawCallback();
	static void GengleEngine::IdleCallback();
	static void GengleEngine::KeyboardCallback(unsigned char key, int x, int y);
	static void GengleEngine::KeyboardUpCallback(unsigned char key, int x, int y);
	static void GengleEngine::MouseCallback(int x, int y);
	static void GengleEngine::SpecialKeyboardCallback(int key, int x, int y);

	glm::vec2 window_size;

	VertexArray* vao = NULL;
	Buffer* arrayBuffer = NULL;
	Buffer* elementBuffer = NULL;

	std::vector<GElement*> elements;
	InputReceiver* inputReceiver = NULL;
	InputTransmitter* inputTransmitter = NULL;
	InputUpdate* inputUpdate = NULL;

	ShaderConfig* shaderConfig = NULL;

	PhysicsEngine* physicsEngine = NULL;

	void GengleEngine::ProcessPhysics(void);
public:
	GengleEngine::GengleEngine(GLint argc, GLchar** argv, glm::vec2 window_size_in);
	GengleEngine::~GengleEngine();

	GElement* GengleEngine::AddBasicElement(BasicElementTypes type);
	void GengleEngine::Start(void);
};

