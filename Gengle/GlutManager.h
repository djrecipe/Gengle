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
private:
	static GLint windowID;
public:
	static GLboolean GlutManager::Initialize(GLint argc, GLchar** argv, glm::vec2 window_size,
		void(*display_callback)(void), void(*idle_callback)(void),
		void(*keyboard)(unsigned char, int, int),
		void(*special_keyboard)(int, int, int),
		void(*mouse_move_callback)(int, int));
	static void GlutManager::Start(void);
	static void GlutManager::Exit(void);
};

#endif // __OmniGlutManager__
