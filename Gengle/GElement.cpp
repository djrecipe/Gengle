#include "GElement.h"

GElement::GElement(VAO * vao_in)
{
	this->vao = vao_in;
	return;
}

GElement::GElement(VAO * vao_in, Buffer* array_buffer_in)
{
	this->vao = vao_in;
	this->arrayBuffer = array_buffer_in;
	return;
}

GElement::GElement(VAO * vao_in, Buffer* array_buffer_in, Buffer* element_buffer_in)
{
	this->vao = vao_in;
	this->arrayBuffer = array_buffer_in;
	this->elementBuffer = element_buffer_in;
	return;
}


GElement::~GElement()
{
}
