#include "InputTransmitter.h"
#include "GlobalTools.h"

#include <glm/gtc/matrix_transform.hpp>

InputTransmitter::InputTransmitter(InputUpdate * input_update_in,
	ShaderUniform * projection_uniform_in, ShaderUniform * view_uniform_in,
	glm::mat4 projection_matrix_in, glm::mat4 view_matrix_in)
{
	this->inputUpdate = input_update_in;
	this->uniformProjection = projection_uniform_in;
	this->uniformView = view_uniform_in;
	this->currentViewMatrix = view_matrix_in;
	this->currentProjectionMatrix = projection_matrix_in;
	return;
}

void InputTransmitter::TransmitUpdate(void)
{
	glm::vec2 angles = this->inputUpdate->GetUpdate();
	if (angles[0] == 0.0f && angles[1] == 0.0f)
		return;
	//dprint("Transmitting Update ::: X: %f | Y: %f", angles[0], angles[1]);
	cumulativeViewAngles[0] += angles[0] * 1.0f;
	cumulativeViewAngles[1] += angles[1] * 1.0f;
	cumulativeViewAngles[1] = fmax(fmin(cumulativeViewAngles[1], 75.0f), -75.0f);
	glm::mat4 view_matrix = glm::rotate(glm::mat4(1.0), glm::radians(cumulativeViewAngles[0]), glm::vec3(0.0, 1.0, 0.0));
	view_matrix = glm::rotate(view_matrix, glm::radians(cumulativeViewAngles[1]), glm::vec3(1.0, 0.0, 0.0));
	this->uniformView->SetValue(view_matrix);
	this->uniformProjection->SetValue(this->currentProjectionMatrix);
	return;
}

InputTransmitter::~InputTransmitter()
{
}
