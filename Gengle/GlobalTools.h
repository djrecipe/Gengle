#pragma once
#ifndef __OmniGlobalTools__
#define __OmniGlobalTools__

#define GLM_ENABLE_EXPERIMENTAL

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib, "GLEW/1.11.0/x32/glew32s.lib")
#pragma comment(lib, "Freeglut/2.8.1/VS2015/x32/freeglut_static.lib")

#include <GLEW/1.11.0/glew.h>

#define BUFFER_OFFSET(x)  ((const void*) (x))

void __cdecl dprint(const GLchar *format, ...);
GLfloat modulus(GLfloat value, GLfloat trim);

#endif // __OmniGlobalTools__

