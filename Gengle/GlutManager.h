#pragma once

#ifndef __OmniGlutManager__
#define __OmniGlutManager__

#include <GLEW/1.11.0/glew.h>  

class GlutManager
{
public:
	static GLboolean GlutManager::Initialize(GLint argc, GLchar** argv);
};

#endif // __OmniGlutManager__
