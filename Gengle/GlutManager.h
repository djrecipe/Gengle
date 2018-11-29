#pragma once

#ifndef __OmniGlutManager__
#define __OmniGlutManager__

#include <GLEW/1.11.0/glew.h> 
#include <glm/vec2.hpp>

#define FREEGLUT_STATIC

#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <Freeglut/2.8.1/VS2013/freeglut.h>	

class GlutManager
{
public:
	static GLboolean GlutManager::Initialize(GLint argc, GLchar** argv, glm::vec2 window_size,
		void(*keyboard)(unsigned char, int, int),
		void(*special_keyboard)(int, int, int),
		void(*mouse_move_callback)(int, int));
};

#endif // __OmniGlutManager__
