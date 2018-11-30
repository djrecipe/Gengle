#pragma once
#include "InputUpdate.h"
#include "ShaderConfig.h"

class InputTransmitter
{
private:
	InputUpdate * inputUpdate;
	ShaderUniform * uniformProjection;
	ShaderUniform * uniformView;
public:
	InputTransmitter::InputTransmitter(InputUpdate * input_update_in,
		ShaderUniform * projection_uniform_in, ShaderUniform * view_uniform_in);
	InputTransmitter::~InputTransmitter();

	void InputTransmitter::TransmitViewUpdate(void);
};

