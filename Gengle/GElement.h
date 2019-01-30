#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/vec2.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Buffer.h"
#include "PhysicsDescriptor.h"
#include "ShaderConfig.h"
#include "VertexArray.h"

class GElement
{
protected:
	GUID id;

	PhysicsDescriptor physics;
	GLboolean enablePhysics = true;

	glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 rotationAxis = glm::vec3(1.0f, 0.0f, 0.0f);

	GLfloat rotationAngle = 0.0f;
	VertexArray* vao;
	Buffer* GElement::arrayBuffer = NULL;
	Buffer* GElement::elementBuffer = NULL;
	ShaderConfig* shaders;

	void GElement::UpdatePhysicsHitbox(void);
public:
	GElement::GElement(ShaderConfig* shaders_in, VertexArray* vao_in);
	GElement::GElement(ShaderConfig* shaders_in, VertexArray* vao_in, Buffer* array_buffer_in);
	GElement::GElement(ShaderConfig* shaders_in, VertexArray* vao_in, Buffer* array_buffer_in, Buffer* element_buffer_in);

	GElement::~GElement();

	void GElement::ConsumePhysicsDescriptor(PhysicsDescriptor descriptor);
	virtual void GElement::Draw(void) = 0;
	virtual void GElement::Prepare(void) = 0;
	GLboolean GElement::GetEnablePhysics(void);
	GUID GElement::GetID(void);
	glm::mat4x4 GElement::GetModelMatrix(void)
	{
		glm::mat4x4 matrix(1.0);
		matrix = glm::translate(matrix, this->physics.Origin);
		matrix = glm::rotate(matrix, this->rotationAngle, this->rotationAxis);
		matrix = glm::scale(matrix, this->scale);
		return matrix;
	}
	PhysicsDescriptor GElement::GetPhysicsDescriptor(void);

	void GElement::SetAcceleration(glm::vec3 value);
	void GElement::SetEnablePhysics(GLboolean value);
	void GElement::SetOrigin(glm::vec3 value)
	{
		this->physics.Origin = value;
		return;
	}
	void GElement::SetRotation(GLfloat angle, glm::vec3 axis)
	{
		this->rotationAngle = angle;
		this->rotationAxis = axis;
		this->UpdatePhysicsHitbox();
		return;
	}
	void GElement::SetScale(glm::vec3 value)
	{
		this->scale = value;
		this->UpdatePhysicsHitbox();
		return;
	}

	void GElement::SetVelocity(glm::vec3 value);
};

