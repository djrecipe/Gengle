#include "InputTransmitter.h"
#include "GlobalTools.h"

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
	this->inputUpdate->SetViewUpdatePending(false);
	// calculate positions
	glm::vec3 cameraPos = this->inputUpdate->GetViewTranslations();
	// calculate angles
	glm::vec2 angles = this->inputUpdate->GetViewAngles();
	glm::vec3 front(0.0);
	front.x = cos(glm::radians(angles[0])) * cos(glm::radians(angles[1]));
	front.y = sin(glm::radians(angles[1]));
	front.z = sin(glm::radians(angles[0])) * cos(glm::radians(angles[1]));
	// calculate view matrix
	glm::mat4 view_matrix = glm::lookAt(cameraPos, cameraPos + glm::normalize(front), glm::vec3(0.0f, 1.0f, 0.0f));
	this->uniformView->SetValue(view_matrix);
	return;
}

InputTransmitter::~InputTransmitter()
{
}
