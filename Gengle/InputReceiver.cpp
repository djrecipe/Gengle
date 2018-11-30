#include "GlobalTools.h"
#include "GlutManager.h"
#include "InputReceiver.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>

InputReceiver::InputReceiver(InputUpdate * input_update_in, glm::vec2 window_size)
{
	this->inputUpdate = input_update_in;
	this->windowSize = window_size;
	return;
}

InputReceiver::~InputReceiver()
{
}

void InputReceiver::ProcessMovementCommand(MovementCommands command)
{
	glm::vec3 direction(0.0);
	direction.x = cos(glm::radians(this->cumulativeViewAngles[1])) * cos(glm::radians(this->cumulativeViewAngles[0]))
		* this->movementSensitivities[0];
	direction.y = sin(glm::radians(this->cumulativeViewAngles[1]))
		* this->movementSensitivities[1];
	direction.z = cos(glm::radians(this->cumulativeViewAngles[1])) * sin(glm::radians(this->cumulativeViewAngles[0]))
		* this->movementSensitivities[2];
	switch (command)
	{
	case MoveForward:
		break;
	case MoveBackward:
		direction *= -1.0;
		break;
	case MoveLeft:
		direction = glm::cross(direction, glm::vec3(0.0, 1.0, 0.0));
		direction *= -1.0;
		break;
	case MoveRight:
		direction = glm::cross(direction, glm::vec3(0.0, 1.0, 0.0));
		break;
	case MoveUp:
		break;
	case MoveDown:
		break;
	}

	this->cumulativeViewTranslations += direction;

	this->inputUpdate->SetViewTranslations(cumulativeViewTranslations);
	this->inputUpdate->SetViewUpdatePending(true);
	return;
}

void InputReceiver::ProcessMouseMovement(int x, int y)
{
	int width_half = this->windowSize[0] / 2;
	int height_half = this->windowSize[1] / 2;
	if (x == width_half && y == height_half)
		return;

	cumulativeViewAngles[0] += (x-width_half) * this->mouseSensitivities[0];
	cumulativeViewAngles[0] = modulus(cumulativeViewAngles[0], 360.0f);
	cumulativeViewAngles[1] += (height_half-y) * this->mouseSensitivities[1];
	cumulativeViewAngles[1] = fmax(fmin(cumulativeViewAngles[1], this->verticalLimits[1]), this->verticalLimits[0]);

	this->inputUpdate->SetViewAngles(cumulativeViewAngles);
	this->inputUpdate->SetViewUpdatePending(true);

	glutWarpPointer(width_half, height_half);
	return;
}

