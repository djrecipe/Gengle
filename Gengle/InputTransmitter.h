#pragma once
#include "InputUpdate.h"
#include "ShaderConfig.h"

class InputTransmitter
{
private:
	InputUpdate * inputUpdate;
	ShaderUniform * uniformProjection;
	ShaderUniform * uniformView;
	glm::mat4x4 currentViewMatrix = glm::mat4x4(1.0);
	glm::mat4x4 currentProjectionMatrix = glm::mat4x4(1.0);
	glm::vec2 cumulativeViewAngles = glm::vec2(0.0, 0.0);
public:
	InputTransmitter::InputTransmitter(InputUpdate * input_update_in,
		ShaderUniform * projection_uniform_in, ShaderUniform * view_uniform_in,
		glm::mat4 projection_matrix_in, glm::mat4 view_matrix_in);
	InputTransmitter::~InputTransmitter();

	void InputTransmitter::TransmitUpdate(void);
};

