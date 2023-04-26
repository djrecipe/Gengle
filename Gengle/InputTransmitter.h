#pragma once
#include "InputUpdate.h"
#include "ShaderConfig.h"

class InputTransmitter
{
private:
	InputUpdate * inputUpdate;
	ShaderUniform * uniformProjection;
	ShaderUniform * uniformView;
	glm::vec3 movementSensitivities = glm::vec3(5.0f, 5.0f, 5.0f);
public:
	InputTransmitter(InputUpdate * input_update_in,
		ShaderUniform * projection_uniform_in, ShaderUniform * view_uniform_in);
	~InputTransmitter();

	void TransmitViewUpdate(void);
};

