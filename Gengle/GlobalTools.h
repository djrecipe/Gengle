#pragma once
#ifndef __OmniGlobalTools__
#define __OmniGlobalTools__

#define FREEGLUT_STATIC
#define GLM_ENABLE_EXPERIMENTAL

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <GLEW/1.11.0/glew.h>
#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <Freeglut/2.8.1/VS2013/freeglut.h>	

#include <assert.h> 
#include <chrono>
#include <combaseapi.h>
#include <iostream>
#include <map>
#include <mutex>
#include <thread>
#include <stdexcept>
#include <vector>


#define BUFFER_OFFSET(x)  ((const void*) (x))

void __cdecl dprint(const GLchar *format, ...);
GLfloat modulus(GLfloat value, GLfloat trim);

struct GUIDComparer
{
	bool operator()(const GUID & Left, const GUID & Right) const
	{
		// comparison logic goes here
		return memcmp(&Left, &Right, sizeof(Right)) < 0;
	}
};

#endif // __OmniGlobalTools__

