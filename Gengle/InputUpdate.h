#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/vec2.hpp>

class InputUpdate
{
private:
	glm::vec2 mouseTranslation = glm::vec2(0.0, 0.0);
public:
	InputUpdate();
	~InputUpdate();

	glm::vec2 GetUpdate(void)
	{
		glm::vec2 value = glm::vec2(this->mouseTranslation);
		this->mouseTranslation = glm::vec2(0.0, 0.0);
		return value;
	}

	void IncrementMouseHorizontal(GLfloat value) { this->mouseTranslation[0] += value; }
	void IncrementMouseVertical(GLfloat value) { this->mouseTranslation[1] += value; }
};

