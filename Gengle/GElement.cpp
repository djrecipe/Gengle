#include "Gengle.pch.h"
#include "GElement.h"

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in)
{
	CoCreateGuid(&this->id);

	this->physics.SetID(this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;

	this->UpdatePhysicsHitbox();
	return;
}

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in, GenericBuffer* array_buffer_in)
{
	CoCreateGuid(&this->id);

	this->physics.SetID(this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;
	this->arrayBuffer = array_buffer_in;

	this->UpdatePhysicsHitbox();
	return;
}

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in, GenericBuffer* array_buffer_in,
	GenericBuffer* texcoord_buffer_in, GenericBuffer* element_buffer_in)
{
	CoCreateGuid(&this->id);

	this->physics.SetID(this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;
	this->arrayBuffer = array_buffer_in;
	this->texCoordBuffer = texcoord_buffer_in;
	this->elementBuffer = element_buffer_in;

	this->UpdatePhysicsHitbox();
	return;
}

GElement::~GElement()
{
	if (this->texture != NULL)
		FreeImage_Unload(this->texture);
}

void GElement::ConsumePhysicsDescriptor(PhysicsDescriptor value)
{
	this->physics = value;
	return;
}

GUID GElement::GetID(void)
{
	return this->id;
}

GLboolean GElement::GetEnablePhysics(void)
{
	return this->enablePhysics;
}

PhysicsDescriptor GElement::GetPhysicsDescriptor(void)
{
	return this->physics;
}

void GElement::SetAcceleration(glm::vec3 value)
{
	this->physics.Acceleration = value;
	return;
}

void GElement::SetEnablePhysics(GLboolean value)
{
	this->enablePhysics = value;
	return;
}

void GElement::SetVelocity(glm::vec3 value)
{
	this->physics.Velocity = value;
	return;
}

void GElement::UpdatePhysicsHitbox(void)
{
	glm::vec3 value = glm::rotate(this->scale, this->rotationAngleOne, this->rotationAxisOne);
	value = glm::rotate(value, this->rotationAngleTwo, this->rotationAxisTwo);
	this->physics.Size = glm::abs(value);
	return;
}