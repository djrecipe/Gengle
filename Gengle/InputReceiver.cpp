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

void InputReceiver::ProcessKeyboardEvent(MovementCommands command, InputKeyStates state)
{
	dprint("Processing keyboard event %d", command);
	this->inputUpdate->SetMovementFlag(command, state == KeyStateDown);
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

