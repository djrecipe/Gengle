#pragma once   

#ifndef __OmniShaders__
#define __OmniShaders__

#include <GLEW/1.11.0/glew.h>  

typedef struct
{
	GLenum       type;
	const GLchar*  filename;
	GLuint       shader;
} ShaderInfo;

class Shaders
{
private:
	static const GLchar* Shaders::ReadShader(const GLchar* filename);
public:
	static GLuint Shaders::LoadShaders(ShaderInfo*);
};

#endif // __OmniShaders__