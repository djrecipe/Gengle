#pragma once

#ifndef __OmniGlutManager__
#define __OmniGlutManager__

#include <GLEW/1.11.0/glew.h>  

class GlutManager
{
public:
	static GLboolean GlutManager::Initialize(GLint argc, GLchar** argv,
		void(*keyboard)(unsigned char, int, int), void(*special_keyboard)(int, int, int));
};

#endif // __OmniGlutManager__
