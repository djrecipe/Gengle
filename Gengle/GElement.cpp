#include "GElement.h"

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in)
{
	CoCreateGuid(&this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;
	return;
}

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in, Buffer* array_buffer_in)
{
	CoCreateGuid(&this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;
	this->arrayBuffer = array_buffer_in;
	return;
}

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in, Buffer* array_buffer_in, Buffer* element_buffer_in)
{
	CoCreateGuid(&this->id);

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
	// TODO 01/29/19: finish real implementation
	this->origin = value.GetOrigin();
	return;
}

GUID GElement::GetID(void)
{
	return this->id;
}

PhysicsDescriptor GElement::GetPhysicsDescriptor(void)
{
	// TODO 01/29/19: finish real implementation
	return PhysicsDescriptor(this->id, glm::vec3(0.1, 0.0, 0.0), this->origin, 1.0);
}