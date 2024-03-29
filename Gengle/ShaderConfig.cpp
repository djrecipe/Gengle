#include "Gengle.pch.h"
#include "ShaderConfig.h" 	

#include "GlobalTools.h"

GLuint ShaderConfig::currentAttributeIndex=0;
#pragma region Static Methods
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

/// <summary>
/// Read shader program text from a file at the specified path
/// </summary>
/// <param name="filename">Shader file path</param>
/// <returns>Shader file contents</returns>
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
#pragma endregion

#pragma region Instance Methods
/// <summary>
/// Create a new shader configuration using the specified parameters
/// </summary>
/// <param name="shaders_in">Shader program file descriptors</param>
ShaderConfig::ShaderConfig(ShaderInfo shaders_in[])
{
	this->SetProgram(shaders_in);
	return;
}

/// <summary>
/// Destroy the shader configuration and delete all shader uniform objects
/// </summary>
ShaderConfig::~ShaderConfig(void)
{
	for(ShaderUniform * uniform : this->uniforms)
	{
		delete uniform;
	}
	this->uniforms.clear();
	return;
}

/// <summary>
/// Create and add a new shader uniform using the specified name
/// </summary>
/// <param name="name">Shader uniform name</param>
void ShaderConfig::AddUniform(const char * name)
{
	ShaderUniform * uniform = new ShaderUniform(name);
	uniform->SetShaderProgram(this->shaderProgram);
	assert(uniform->GetLocation() > -1);
	this->uniforms.push_back(uniform);
	return;
}
void ShaderConfig::AddAttribute(VertexAttribute* attribute)
{
	this->attributes.push_back(attribute);
}

/// <summary>
/// Retrieve the shader uniform associated with the specified name
/// </summary>
/// <param name="name">Shader uniform name to find</param>
/// <returns>Shader uniform</returns>
/// <exception cref="std::runtime_error">Failed to find a shader uniform with the specified name</exception>
ShaderUniform* ShaderConfig::GetUniform(const char* name)
{
	for (int i = 0; i < this->uniforms.size(); i++)
	{
		if (this->uniforms[i]->GetName() == name)
			return this->uniforms[i];
	}
	throw std::runtime_error("Failed to find uniform '" + std::string(name) + "'");
}
VertexAttribute* ShaderConfig::GetAttribute(const char* name)
{
	for (int i = 0; i < this->attributes.size(); i++)
	{
		if (this->attributes[i]->GetName() == name)
			return this->attributes[i];
	}
	throw std::runtime_error("Failed to find attribute '" + std::string(name) + "'");
}

/// <summary>
/// Enable and prepare the shader program for usage
/// </summary>
void ShaderConfig::Prepare(void)
{
	GLint id;
	glGetIntegerv(GL_CURRENT_PROGRAM, &id);
	if (id == this->shaderProgram)
		return;
	// enable shader program
	glUseProgram(this->shaderProgram);
	// configure shader attributes
	return;
}


/// <summary>
/// Load the specified shader program files and store the shader program index
/// </summary>
/// <param name="shaders">Shader program file descriptors</param>
void ShaderConfig::SetProgram(ShaderInfo shaders[])
{
	this->shaderProgram = ShaderConfig::LoadShaders(shaders);
	return;
}
#pragma endregion
