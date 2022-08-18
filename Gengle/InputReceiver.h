#pragma once
#include "GlobalTools.h"
#include "InputUpdate.h"

#include <glm/vec3.hpp>

#define PI_OVER_180 3.141459f/180.0f

class InputReceiver
{
private:
	InputUpdate * inputUpdate = NULL;
	glm::vec2 windowSize;
	glm::vec2 cumulativeViewAngles = glm::vec2(0.0, 0.0);
	glm::vec3 cumulativeViewTranslations = glm::vec3(0.0, 0.0, 0.0);
	glm::vec2 mouseSensitivities = glm::vec2(0.1f, 0.1f);
	glm::vec2 verticalLimits = glm::vec2(-85.0f, 85.0f);
public:
	InputReceiver(InputUpdate * input_update_in, glm::vec2 window_size);
	~InputReceiver();
	void ProcessKeyboardEvent(MovementCommands command, InputKeyStates state);
	void ProcessMouseMovement(int x, int y);
	void SetMouseSensitivities(GLfloat x, GLfloat y)
	{
		this->mouseSensitivities = glm::vec2(x, y);
		return;
	}
	void SetVerticalLimits(GLfloat lower, GLfloat upper)
	{
		this->verticalLimits = glm::vec2(lower, upper);
		return;
	}
};

