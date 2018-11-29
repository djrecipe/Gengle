#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Buffer.h"
#include "ShaderConfig.h"
#include "VAO.h"

class GElement
{
protected:
	glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);
	GLfloat rotationAngle = 0.0f;
	VAO* vao;
	Buffer* GElement::arrayBuffer = NULL;
	Buffer* GElement::elementBuffer = NULL;
	ShaderConfig shaders;
public:
	GElement(ShaderConfig shaders_in, VAO* vao_in);
	GElement(ShaderConfig shaders_in, VAO* vao_in, Buffer* array_buffer_in);
	GElement(ShaderConfig shaders_in, VAO* vao_in, Buffer* array_buffer_in, Buffer* element_buffer_in);
	virtual void Draw(void) = 0;
	virtual void Prepare(void) = 0;
	glm::mat4x4 GetModelMatrix(void)
	{
		glm::mat4x4 matrix(1.0);
		matrix = glm::translate(matrix, this->origin);
		matrix = glm::rotate(matrix, this->rotationAngle, this->rotationAxis);
		matrix = glm::scale(matrix, this->scale);
		return matrix;
	}
	void SetOrigin(glm::vec3 value)
	{
		this->origin = value;
		return;
	}
	void SetRotation(GLfloat angle, glm::vec3 axis)
	{
		this->rotationAngle = angle;
		this->rotationAxis = axis;
		return;
	}
	void SetScale(glm::vec3 value)
	{
		this->scale = value;
		return;
	}
	~GElement();
};

