#include "ShaderConfig.h" 		
#include "GlobalTools.h"
#include <iostream>

GLuint ShaderConfig::LoadShaders(ShaderInfo* shaders)
{
	if (shaders == NULL)
	{
		return 0;
	}

	GLuint program = glCreateProgram();

	ShaderInfo* entry = shaders;
	while (entry->type != GL_NONE)
	{
		GLuint new_shader = glCreateShader(entry->type);

		entry->shader = new_shader;

		const GLchar* source = ShaderConfig::ReadShader(entry->filename);
		if (source == NULL)
		{
			for (entry = shaders; entry->type != GL_NONE; ++entry) {
				glDeleteShader(entry->shader);
				entry->shader = 0;
			}

			return 0;
		}

		glShaderSource(new_shader, 1, &source, NULL);
		delete[] source;

		glCompileShader(new_shader);

		GLint compiled;
		glGetShaderiv(new_shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLsizei len;
			glGetShaderiv(new_shader, GL_INFO_LOG_LENGTH, &len);

			GLchar* log = new GLchar[len + 1];
			glGetShaderInfoLog(new_shader, len, &len, log);
			dprint("Shader compilation failed: %s", log);
			delete[] log;
			return 0;
		}

		glAttachShader(program, new_shader);

		++entry;
	}
	glLinkProgram(program);

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		GLsizei len;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);

		GLchar* log = new GLchar[len + 1];
		glGetProgramInfoLog(program, len, &len, log);
		dprint("Shader linking failed: %s", log);
		delete[] log;
		for (entry = shaders; entry->type != GL_NONE; ++entry) {
			glDeleteShader(entry->shader);
			entry->shader = 0;
		}

		return 0;
	}

	return program;
}
const GLchar* ShaderConfig::ReadShader(const GLchar* filename)
{
	FILE* infile;
	fopen_s(&infile, filename, "rb");

	if (!infile)
	{
		dprint("Unable to open file '%s'", filename);
		return NULL;
	}

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek(infile, 0, SEEK_SET);

	GLchar* source = new GLchar[len + 1];

	fread(source, 1, len, infile);
	fclose(infile);

	source[len] = 0;

	return const_cast<const GLchar*>(source);
}

ShaderConfig::ShaderConfig()
{

}

ShaderConfig::ShaderConfig(ShaderInfo shaders_in[], std::vector<VertexAttribute> attributes_in, std::vector<ShaderUniform*> uniforms_in)
{
	this->SetProgram(shaders_in);
	this->SetAttributes(attributes_in);
	this->SetUniforms(uniforms_in);
	return;
}

void ShaderConfig::Prepare(void)
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	if (id == this->shaderProgram)
		return;
	// enable shader program
	glUseProgram(this->shaderProgram);
	// configure shader attributes
	for (VertexAttribute attribute : this->attributes)
	{
		attribute.Prepare();
		attribute.Enable();
	}
	return;
}

void ShaderConfig::SetAttributes(std::vector<VertexAttribute> attributes_in)
{
	this->attributes.clear();
	for (int i = 0; i < attributes_in.size(); i++)
		this->attributes.push_back(attributes_in[i]);
	return;
}

void ShaderConfig::SetProgram(ShaderInfo shaders[])
{
	this->shaderProgram = ShaderConfig::LoadShaders(shaders);
	return;
}

void ShaderConfig::SetUniforms(std::vector<ShaderUniform*> uniforms_in)
{
	this->uniforms.clear();
	for (int i = 0; i < uniforms_in.size(); i++)
	{
		this->uniforms.push_back(uniforms_in[i]);
		this->uniforms[i]->SetShaderProgram(this->shaderProgram);
	}
	return;
}

