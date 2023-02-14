#pragma once

/// <summary>
/// Shader uniform variable descriptor and function wrapper
/// </summary>
class ShaderUniform
{
private:
	const char* name;
	GLint shaderProgram;
	glm::mat4x4 value_mat4;
	bool value_bool;
public:
	// construction/destruction
	ShaderUniform(const char * name_in);
	~ShaderUniform();
	// getters
	GLint GetLocation(void);
	const char* GetName(void);
	// setters
	void SetShaderProgram(GLint program);
	// value setters
	void SetValue(glm::mat4x4 value);
	void SetValue(bool value);
};
