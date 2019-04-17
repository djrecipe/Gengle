#include <iostream>
#include <vector>
using namespace std;

#define FREEGLUT_STATIC

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <GLEW/1.11.0/glew.h>

#include "GlobalTools.h"    
#include "Cube.h"
#include "Triangle.h"
#include "GengleEngine.h"
#include "GlutManager.h"

int main(int argc, char** argv)
{
	glm::vec2 window_size = glm::vec2(1280, 960);
	// create engine
	GengleEngine engine(argc, argv, window_size);
	// define elements
	GElement * element = NULL;
	element = engine.AddBasicElement(SphereElement);
	element->SetScale(glm::vec3(200.0, 100.0, 40.0));
	element->SetRotation(glm::radians(70.0f), glm::vec3(0.0, 1.0, 1.0));
	element->SetOrigin(glm::vec3(10.0, -10.0, 0.0));
	// start display loop
	engine.Start();
	// end program
	return 0;
}
