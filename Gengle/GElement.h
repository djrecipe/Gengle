#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/vec2.hpp>

class GElement
{
protected:
	glm::vec2 origin = glm::vec2(0.0f, 0.0f);
public:
	GElement();
	~GElement();
};

