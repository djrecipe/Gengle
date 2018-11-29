#include "InputTransmitter.h"
#include "GlobalTools.h"

#include <glm/gtc/matrix_transform.hpp>

InputTransmitter::InputTransmitter(InputUpdate * input_update_in, ShaderUniform * pvm_uniform_in)
{
	this->inputUpdate = input_update_in;
	this->uniformPvm = pvm_uniform_in;
	return;
}

void InputTransmitter::TransmitUpdate(void)
{
	glm::vec2 angles = this->inputUpdate->GetUpdate();
	if (angles[0] == 0.0f && angles[1] == 0.0f)
		return;
	//dprint("Transmitting Update ::: X: %f | Y: %f", angles[0], angles[1]);
	this->currentProjectionViewMatrix = glm::rotate(this->currentProjectionViewMatrix, angles[0] * 0.01f, glm::vec3(0.0, 1.0, 0.0));
	this->currentProjectionViewMatrix = glm::rotate(this->currentProjectionViewMatrix, angles[1] * 0.01f, glm::vec3(1.0, 0.0, 0.0));
	this->uniformPvm->SetValue(this->currentProjectionViewMatrix);
	return;
}

InputTransmitter::~InputTransmitter()
{
}
