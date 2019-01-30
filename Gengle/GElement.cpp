#include "GElement.h"

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in)
{
	CoCreateGuid(&this->id);

	this->physics.SetID(this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;
	return;
}

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in, Buffer* array_buffer_in)
{
	CoCreateGuid(&this->id);

	this->physics.SetID(this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;
	this->arrayBuffer = array_buffer_in;
	return;
}

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in, Buffer* array_buffer_in, Buffer* element_buffer_in)
{
	CoCreateGuid(&this->id);

	this->physics.SetID(this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;
	this->arrayBuffer = array_buffer_in;
	this->elementBuffer = element_buffer_in;
	return;
}

GElement::~GElement()
{
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

PhysicsDescriptor GElement::GetPhysicsDescriptor(void)
{
	return this->physics;
}

void GElement::SetAcceleration(glm::vec3 value)
{
	this->physics.Acceleration = value;
	return;
}

void GElement::SetVelocity(glm::vec3 value)
{
	this->physics.Velocity = value;
	return;
}