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
	GLuint shaderProgram = -1;
	std::vector<VertexAttribute> attributes;
	std::vector<ShaderUniform*> uniforms;
	static GLuint LoadShaders(ShaderInfo*);
	static const GLchar* ReadShader(const GLchar* filename);
public:
	ShaderConfig(ShaderInfo shaders_in[], std::vector<VertexAttribute> attributes_in);
	~ShaderConfig();

	void AddUniform(const char * name);
	ShaderUniform* GetUniform(const char * name);
	void Prepare(void);
	void SetAttributes(std::vector<VertexAttribute> attributes_in);
	void SetProgram(ShaderInfo shaders_in[]);
};

#endif // __OmniShaders__