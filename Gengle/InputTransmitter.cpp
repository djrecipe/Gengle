#include "InputTransmitter.h"
#include "GlobalTools.h"
#include "GlutManager.h"

#include <glm/gtc/matrix_transform.hpp>

InputTransmitter::InputTransmitter(InputUpdate * input_update_in,
	ShaderUniform * projection_uniform_in, ShaderUniform * view_uniform_in)
{
	this->inputUpdate = input_update_in;
	this->uniformProjection = projection_uniform_in;
	this->uniformView = view_uniform_in;
	return;
}

void InputTransmitter::TransmitViewUpdate(void)
{
	if (!this->inputUpdate->GetViewUpdatePending())
		return;
	// calculate camera target
	glm::vec2 angles = this->inputUpdate->GetViewAngles();
	glm::vec3 direction(0.0);
	direction.x = cos(glm::radians(angles[0])) * cos(glm::radians(angles[1])) * this->movementSensitivities[0];
	direction.y = sin(glm::radians(angles[1])) * this->movementSensitivities[1];
	direction.z = sin(glm::radians(angles[0])) * cos(glm::radians(angles[1])) * this->movementSensitivities[2];
	// calculate camera origin
	glm::vec3 cameraPos = this->inputUpdate->GetViewTranslations();
	MovementCommands movement = this->inputUpdate->GetMovementFlags();
	if ((movement & MoveForward) != 0)
	{
		cameraPos += direction;
	}
	if ((movement & MoveBackward) != 0)
	{
		cameraPos -= direction;
	}
	if ((movement & MoveLeft) != 0)
	{
		cameraPos -= glm::cross(direction, glm::vec3(0.0, 1.0, 0.0));
	}
	if ((movement & MoveRight) != 0)
	{
		cameraPos += glm::cross(direction, glm::vec3(0.0, 1.0, 0.0));
	}
	// calculate view matrix
	glm::mat4 view_matrix = glm::lookAt(cameraPos, cameraPos + glm::normalize(direction), glm::vec3(0.0f, 1.0f, 0.0f));
	// transmit view matrix
	this->uniformView->SetValue(view_matrix);
	// update cumulative view translation
	this->inputUpdate->SetViewTranslations(cameraPos);
	// force screen refresh
	glutPostRedisplay();
	return;
}

InputTransmitter::~InputTransmitter()
{
}
