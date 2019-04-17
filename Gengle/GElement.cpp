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

GElement::GElement(ShaderConfig* shaders_in, VertexArray * vao_in, Buffer* array_buffer_in)
{
	CoCreateGuid(&this->id);

	this->physics.SetID(this->id);

	this->shaders = shaders_in;
	this->vao = vao_in;
	this->arrayBuffer = array_buffer_in;

	this->UpdatePhysicsHitbox();
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

	this->UpdatePhysicsHitbox();
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

void GElement::DrawHitbox(void)
{
	return;
}

GUID GElement::GetID(void)
{
	return this->id;
}

GLboolean GElement::GetDrawHitbox(void)
{
	return this->drawHitbox;
}

GLboolean GElement::GetEnablePhysics(void)
{
	return this->enablePhysics;
}

PhysicsDescriptor GElement::GetPhysicsDescriptor(void)
{
	return this->physics;
}

void GElement::PrepareHitbox(void)
{
	// configure shaders
	this->shaders->Prepare();
	// send uniform values
	this->shaders->GetUniform("modelMatrix")->SetValue(this->GetModelMatrix());
	this->shaders->GetUniform("inputColor")->SetValue(glm::vec4(0.9, 0.1, 0.05, 0.1));
	// activate vertex array object
	this->vao->Activate();
	// activate array buffer
	this->arrayBuffer->Activate();
	// send data to activated buffer
	GLfloat vertices[NumHitboxVertices][3] = {
		{ -1.0f, -1.0f, -1.0f },
		{ -1.0f, -1.0f,  1.0f },
		{ -1.0f,  1.0f,  1.0f },
		{  1.0f,  1.0f,  1.0f },
		{  1.0f,  1.0f, -1.0f },
		{  1.0f, -1.0f, -1.0f },
		{ -1.0f,  1.0f, -1.0f },
		{  1.0f, -1.0f,  1.0f } };
	this->arrayBuffer->SendData(vertices, sizeof(vertices));
	// activate element buffer
	this->elementBuffer->Activate();
	// send data to activated buffer
	GLuint indices[NumHitboxIndices] = { 0, 5, 4, 4, 6, 0, 6, 4, 3, 3, 2, 6, 2, 3, 7, 7, 1, 2, 1, 7, 5, 5, 0, 1, 0, 1, 2, 2, 6, 0, 5, 7, 3, 3, 4, 5 };
	this->elementBuffer->SendData(indices, sizeof(indices));
	//
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPointSize(1.0f);
	return;
}

void GElement::SetAcceleration(glm::vec3 value)
{
	this->physics.Acceleration = value;
	return;
}

void GElement::SetDrawHitbox(GLboolean value)
{
	this->drawHitbox = value;
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