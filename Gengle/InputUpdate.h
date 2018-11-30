#pragma once
#include <GLEW/1.11.0/glew.h>  
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

class InputUpdate
{
private:
	glm::vec2 viewAngles = glm::vec2(0.0, 0.0);
	glm::vec3 viewTranslations = glm::vec3(0.0, 0.0, 0.0);
	GLboolean pendingViewUpdate = false;
public:
	InputUpdate();
	~InputUpdate();

	GLboolean GetViewUpdatePending(void)
	{
		return this->pendingViewUpdate;
	}

	void SetViewUpdatePending(GLboolean value)
	{
		this->pendingViewUpdate = value;
		return;
	}

	glm::vec2 GetViewAngles(void) { return this->viewAngles; }
	void SetViewAngles(glm::vec2 value) { this->viewAngles = value; }

	glm::vec3 GetViewTranslations(void) { return this->viewTranslations;}
	void SetViewTranslations(glm::vec3 value) { this->viewTranslations = value; }
};

