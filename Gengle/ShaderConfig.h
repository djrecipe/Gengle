#pragma once   

#ifndef __OmniShaderConfig__
#define __OmniShaderConfig__

#include <GLEW/1.11.0/glew.h>  

#include "VertexAttribute.h"

#include <vector>

typedef struct
{
	GLenum       type;
	const GLchar*  filename;
	GLuint       shader;
} ShaderInfo;

class ShaderConfig
{
private:
	GLuint ShaderConfig::shaderProgram = -1;
	std::vector<VertexAttribute> ShaderConfig::attributes;
	static GLuint ShaderConfig::LoadShaders(ShaderInfo*);
	static const GLchar* ShaderConfig::ReadShader(const GLchar* filename);
public:
	ShaderConfig::ShaderConfig();
	ShaderConfig::ShaderConfig(ShaderInfo shaders[], std::vector<VertexAttribute> attributes);
	void ShaderConfig::Prepare(void);
	void ShaderConfig::SetAttributes(std::vector<VertexAttribute> attributes);
	void ShaderConfig::SetProgram(ShaderInfo shaders[]);
};

#endif // __OmniShaders__