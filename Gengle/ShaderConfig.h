#pragma once   

#ifndef __OmniShaderConfig__
#define __OmniShaderConfig__

#include "GlobalTools.h"
#include "ShaderUniform.h"
#include "VertexAttribute.h"

/// <summary>
/// Shader program file (.hlsl) descriptor
/// </summary>
typedef struct
{
	GLenum       type;
	const GLchar*  filename;
	GLuint       shader;
} ShaderInfo;

/// <summary>
/// Shader program(s) configuration descriptor and function wrapper
/// </summary>
class ShaderConfig
{
private:
	GLuint ShaderConfig::shaderProgram = -1;
	std::vector<VertexAttribute> ShaderConfig::attributes;
	std::vector<ShaderUniform*> ShaderConfig::uniforms;
	static GLuint ShaderConfig::LoadShaders(ShaderInfo*);
	static const GLchar* ShaderConfig::ReadShader(const GLchar* filename);
public:
	ShaderConfig::ShaderConfig(ShaderInfo shaders_in[], std::vector<VertexAttribute> attributes_in);
	ShaderConfig::~ShaderConfig();

	void ShaderConfig::AddUniform(const char * name);
	ShaderUniform* ShaderConfig::GetUniform(const char * name);
	void ShaderConfig::Prepare(void);
	void ShaderConfig::SetAttributes(std::vector<VertexAttribute> attributes_in);
	void ShaderConfig::SetProgram(ShaderInfo shaders_in[]);
};

#endif // __OmniShaders__