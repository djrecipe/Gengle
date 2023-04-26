#pragma once

#define FREEGLUT_STATIC
#define GLM_ENABLE_EXPERIMENTAL
#define WIN32_LEAN_AND_MEAN
#define BUFFER_OFFSET(x)  ((const void*) (x))


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")
#pragma comment(lib, "FreeType/2.9.1/x32/freetype.lib")


#include <algorithm>
#include <assert.h> 
#include <combaseapi.h>
#include <chrono>
#include <cstring>
#include <ctime>
#include <cmath>
#include <cassert>
#include <exception>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <ostream>
#include <thread>
#include <stdexcept>
#include <stack>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <strsafe.h>
#include <sstream>
#include <thread>
#include <vector>
#include <windows.h>

#include <GLEW/1.11.0/glew.h>

#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/noise.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>
#include <glm/vec2.hpp>

#include <Freeglut/2.8.1/VS2013/freeglut.h>
#include <FreeImage/FreeImage.h>
#ifndef FT2BUILD_H_
#define FT2BUILD_H_
#include <FreeType/2.9.1/freetype/config/ftheader.h>
#endif



#include "GlobalTools.h"    
#include "CubeGElement.h"
#include "TriangleGElement.h"
#include "GengleEngine.h"
#include "GlutManager.h"
#include "VoxelCubeArrayGElement.h"

int main(int argc, char** argv)
{
	glm::vec2 window_size = glm::vec2(1600, 900);
	// create engine
	GengleEngine engine(argc, argv, window_size);
	// define elements
	GElement * element = NULL;
	element = engine.AddBasicElement(CubeElement);
	element->SetScale(glm::vec3(10.0, 10.0, 10.0));
	element->SetRotation(glm::radians(70.0f), glm::vec3(0.0, 1.0, 1.0));
	element->SetOrigin(glm::vec3(100.0, -100.0, 0100.0));
	element->SetTexture("BoxTexture.jpg");
	//
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int z = 0; z < 3; z++)
			{

				VoxelCubeArrayGElement* voxel_element = (VoxelCubeArrayGElement*)engine.AddBasicElement(VoxelElement);
				voxel_element->SetOrigin(glm::vec3(x*256.0, y*256.0, z*256.0));
				voxel_element->SetScale(glm::vec3(4.0, 4.0, 4.0));
				voxel_element->SetVoxelCubeCount(40);
				voxel_element->GenerateVertices(x, y, z);
			}
		}
	}
	// start display loop
	engine.StartWithGlut();
	// end program
	return 0;
}
