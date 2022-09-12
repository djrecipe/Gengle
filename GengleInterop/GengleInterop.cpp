#pragma once
#include <iostream>
#include <vector>

#include "AxisGElement.h"
#include "WindowManager.h"
using namespace std;

#define FREEGLUT_STATIC

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <GLEW/1.11.0/glew.h>

#include "GlobalTools.h"    
#include "CubeGElement.h"
#include "TriangleGElement.h"
#include "GengleEngine.h"
#include "GlutManager.h"
#include "VoxelCubeArrayGElement.h"
namespace Gengle
{
namespace Interop
{
extern "C"
{
GengleEngine* engine;
void ChangeSize(double width, double height)
{
	WindowManager::ChangeSize(width, height);
}
void CreateNewWindow(void* hwndParent, void*& result)
{
	result = WindowManager::CreateNewWindow((HWND)hwndParent);
}
void Demo(void)
{
	glm::vec2 window_size = glm::vec2(1600, 900);
	// create engine
	char* args[] = {(char*)" "};
	GengleEngine engine(0, args, window_size);
	// define elements
	GElement* element = new AxisGElement();
	element = engine.AddBasicElement(element);
	//element->SetScale(glm::vec3(10.0, 10.0, 10.0));
	//element->SetRotation(glm::radians(70.0f), glm::vec3(0.0, 1.0, 1.0));
	//element->SetOrigin(glm::vec3(10.0, -10.0, 0.0));
	//element->SetTexture((GLchar*)"BoxTexture.jpg");
	////
	//VoxelCubeArrayGElement* voxel_element = (VoxelCubeArrayGElement*)engine.AddBasicElement(VoxelElement);
	//voxel_element->SetOrigin(glm::vec3(0.0, 0.0, 0.0));
	//voxel_element->SetScale(glm::vec3(4.0, 4.0, 4.0));
	//voxel_element->SetVoxelCubeCount(40);
	//voxel_element->GenerateVertices();
	// start display loop
	engine.StartWithGlut();
}
void Cleanup(void* handle)
{
	WindowManager::Cleanup((HWND)handle);
}
void GetScale(double& scale_x, double& scale_y)
{
	WindowManager::GetScale(scale_x, scale_y);
}
void InitializeOpengl(void* hwnd)
{
	//Demo(); // still works
	//return;
	WindowManager::SetGlContext((HWND)hwnd);
	// create engine
	engine = new GengleEngine();
	GElement* element1 = new AxisGElement();
	element1 = engine->AddBasicElement(element1);
	element1->SetScale(glm::vec3(1.0, 1.0, 1.0));
	element1->SetOrigin(glm::vec3(0.0, 0.0, -10.0));
	GElement* element2 = new AxisGElement();
	element2 = engine->AddBasicElement(element2);
	element2->SetScale(glm::vec3(1.0, 1.0, 1.0));
	element2->SetOrigin(glm::vec3(0.0, 0.0, -10.0));
	element2->SetRotation(90.0, glm::vec3(0.0, 0.0, 1.0));
	//// define elements [get initialization working first]
	//GElement* element = NULL;
	//element = engine->AddBasicElement(CubeElement);
	//element->SetScale(glm::vec3(10.0, 10.0, 10.0));
	//element->SetRotation(glm::radians(70.0f), glm::vec3(0.0, 1.0, 1.0));
	//element->SetOrigin(glm::vec3(10.0, -10.0, 0.0));
	//element->SetTexture((GLchar*)"BoxTexture.jpg");
	////
	//VoxelCubeArrayGElement* voxel_element = (VoxelCubeArrayGElement*)engine->AddBasicElement(VoxelElement);
	//voxel_element->SetOrigin(glm::vec3(0.0, 0.0, 0.0));
	//voxel_element->SetScale(glm::vec3(4.0, 4.0, 4.0));
	//voxel_element->SetVoxelCubeCount(40);
	//voxel_element->GenerateVertices();
	//// start display loop
	engine->StartWithoutGlut();
	return;
}
void Render()
{
	WindowManager::BeginRenderIteration();
	engine->DrawIteration();
	WindowManager::EndRenderIteration();
	//WindowManager::Render();
}
}
}
}