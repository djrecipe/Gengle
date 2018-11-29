#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/vec2.hpp>

class InputUpdate
{
private:
	glm::vec2 angle = glm::vec2(0.0, 0.0);
public:
	InputUpdate();
	~InputUpdate();
	GLfloat GetAngleSide(void) { return this->angle[0]; }
	GLfloat GetAngleUp(void) { return this->angle[1]; }

	void AddHorizontalAngle(GLfloat value)
	{
		angle[0] += value;
		return;
	}

	void AddVerticalAngle(GLfloat value)
	{
		angle[1] += value;
		return;
	}

	glm::vec2 GetUpdate(void)
	{
		glm::vec2 value = glm::vec2(this->angle);
		this->angle = glm::vec2(0.0, 0.0);
		return value;
	}
};

