#pragma once
#include "GlobalTools.h"
#include "InputUpdate.h"

#include <glm/vec3.hpp>

#define PI_OVER_180 3.141459f/180.0f

enum MovementCommands : GLuint { MoveForward, MoveBackward, MoveLeft, MoveRight, MoveUp, MoveDown };

class InputReceiver
{
private:
	InputUpdate * inputUpdate = NULL;
	glm::vec2 windowSize;
	glm::vec2 cumulativeViewAngles = glm::vec2(0.0, 0.0);
	glm::vec3 cumulativeViewTranslations = glm::vec3(0.0, 0.0, 0.0);
	glm::vec2 mouseSensitivities = glm::vec2(1.0f, 1.0f);
	glm::vec3 movementSensitivities = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec2 verticalLimits = glm::vec2(-85.0f, 85.0f);
public:
	InputReceiver::InputReceiver(InputUpdate * input_update_in, glm::vec2 window_size);
	InputReceiver::~InputReceiver();
	void InputReceiver::ProcessMovementCommand(MovementCommands command);
	void InputReceiver::ProcessMouseMovement(int x, int y);
	void InputReceiver::SetMouseSensitivities(GLfloat x, GLfloat y)
	{
		this->mouseSensitivities = glm::vec2(x, y);
		return;
	}
	void InputReceiver::SetMovementSensitivities(GLfloat x, GLfloat y, GLfloat z)
	{
		this->movementSensitivities = glm::vec3(x, y, z);
		return;
	}
	void InputReceiver::SetVerticalLimits(GLfloat lower, GLfloat upper)
	{
		this->verticalLimits = glm::vec2(lower, upper);
		return;
	}
};

