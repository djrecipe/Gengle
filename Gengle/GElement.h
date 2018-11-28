#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/vec2.hpp>

#include "Buffer.h"
#include "VAO.h"

class GElement
{
protected:
	glm::vec2 origin = glm::vec2(0.0f, 0.0f);
	VAO* vao;
	Buffer* GElement::arrayBuffer;
	Buffer* GElement::elementBuffer;
public:
	GElement(VAO* vao_in);
	GElement(VAO* vao_in, Buffer* array_buffer_in);
	GElement(VAO* vao_in, Buffer* array_buffer_in, Buffer* element_buffer_in);
	virtual void Draw(void) = 0;
	virtual void Prepare(void) = 0;
	~GElement();
};

