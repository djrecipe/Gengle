#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/mat4x4.hpp>

class ShaderUniform
{
private:
	const char* name;
	GLint shaderProgram;

	glm::mat4x4 value_mat4;
public:
	//
	ShaderUniform(const char * name_in);
	~ShaderUniform();
	//
	GLint GetLocation(void) { return glGetUniformLocation(this->shaderProgram, this->name); }
	const char * GetName(void) { return this->name; }
	void SetShaderProgram(GLint program) { this->shaderProgram = program; }
	void SetValue(glm::mat4x4 value)
	{
		this->value_mat4 = value;
		GLint location = this->GetLocation();
		assert(location > -1);
		glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
		return;
	}
};
