#include "ShaderUniform.h"

#pragma region Instance Methods
/// <summary>
/// Define a new shader uniform associated with the specified name
/// </summary>
/// <param name="name_in">Uniform name</param>
ShaderUniform::ShaderUniform(const char * name_in)
{
	this->name = name_in;
	return;
}

/// <summary>
/// Destroy the shader uniform descriptor
/// </summary>
ShaderUniform::~ShaderUniform()
{
}

/// <summary>
/// Retrieve the index which represents the uniform within the shader program
/// </summary>
/// <returns>Index/identifier</returns>
GLint ShaderUniform::GetLocation(void)
{
	return glGetUniformLocation(this->shaderProgram, this->name);
}

/// <summary>
/// Retrieve the shader uniform name
/// </summary>
/// <returns>Uniform name</returns>
const char * ShaderUniform::GetName(void)
{
	return this->name;
}

/// <summary>
/// Set the shader uniform's program indentifier to the specified index
/// </summary>
/// <param name="program">Index of the shader program that contains this uniform variable</param>
void ShaderUniform::SetShaderProgram(GLint program)
{
	this->shaderProgram = program;
	return;
}

/// <summary>
/// Set the shader uniform value to the specified 4x4 matrix value
/// </summary>
/// <param name="value">4x4 matrix value to assign to the uniform variable</param>
void ShaderUniform::SetValue(glm::mat4x4 value)
{
	this->value_mat4 = value;
	GLint location = this->GetLocation();
	assert(location > -1);
	glUniformMatrix4fv(location, 1, GL_FALSE, &value[0][0]);
	return;
}
#pragma endregion