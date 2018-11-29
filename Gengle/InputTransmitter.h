#pragma once
#include "InputUpdate.h"
#include "ShaderConfig.h"

class InputTransmitter
{
private:
	InputUpdate * inputUpdate;
	ShaderUniform * uniformPvm;
	glm::mat4x4 currentProjectionViewMatrix = glm::mat4x4(1.0);
public:
	InputTransmitter::InputTransmitter(InputUpdate * input_update_in, ShaderUniform * pvm_uniform_in);
	InputTransmitter::~InputTransmitter();

	void InputTransmitter::TransmitUpdate(void);
};

