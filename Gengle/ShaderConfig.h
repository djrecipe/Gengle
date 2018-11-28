#pragma once   

#ifndef __OmniShaderConfig__
#define __OmniShaderConfig__

#include <GLEW/1.11.0/glew.h>  

#include "ShaderUniform.h"
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
	std::vector<ShaderUniform> ShaderConfig::uniforms;
	static GLuint ShaderConfig::LoadShaders(ShaderInfo*);
	static const GLchar* ShaderConfig::ReadShader(const GLchar* filename);
public:
	ShaderConfig::ShaderConfig();
	ShaderConfig::ShaderConfig(ShaderInfo shaders_in[],
		std::vector<VertexAttribute> attributes_in, std::vector<ShaderUniform> uniforms_in);
	void ShaderConfig::Prepare(void);
	void ShaderConfig::SetAttributes(std::vector<VertexAttribute> attributes_in);
	void ShaderConfig::SetProgram(ShaderInfo shaders_in[]);
	void ShaderConfig::SetUniforms(std::vector<ShaderUniform> uniforms_in);
};

#endif // __OmniShaders__