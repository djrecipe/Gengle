#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/mat4x4.hpp>

class ShaderUniform
{
private:
	const char* name;
	GLenum type;
	GLint shaderProgram;
public:
	//
	ShaderUniform(const char * name_in, GLenum type_in);
	~ShaderUniform();
	//
	GLint GetLocation(void) { return glGetUniformLocation(this->shaderProgram, this->name); }
	const char * GetName(void) { return this->name; }
	GLenum GetType(void) { return this->type; }
	void SetShaderProgram(GLint program) { this->shaderProgram = program; }
	void SetValue(glm::mat4x4 value) { glUniformMatrix4fv(this->GetLocation(), 1, GL_FALSE, &value[0][0]); }
};

