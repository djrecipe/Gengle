#include "Shaders.h" 		
#include "GlobalTools.h"
#include <iostream>

GLuint Shaders::LoadShaders(ShaderInfo* shaders)
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

		const GLchar* source = Shaders::ReadShader(entry->filename);
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

const GLchar* Shaders::ReadShader(const char* filename)
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
