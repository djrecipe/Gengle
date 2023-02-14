#pragma once
#ifndef __OmniGlobalTools__
#define __OmniGlobalTools__

#include "guiddef.h"

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

