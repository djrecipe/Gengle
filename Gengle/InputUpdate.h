#pragma once
#include "GlobalTools.h"

/// <summary>
/// Input update data
/// </summary>
/// <remarks>Input data from a user which may be relevant to render parameters/matrices</remarks>
class InputUpdate
{
private:
	GLboolean pendingViewUpdate = false;

	glm::vec2 viewAngles = glm::vec2(0.0, 0.0);
	glm::vec3 viewTranslations = glm::vec3(0.0, 0.0, 0.0);
public:
	InputUpdate::InputUpdate();
	InputUpdate::~InputUpdate();

	glm::vec2 InputUpdate::GetViewAngles(void);
	glm::vec3 InputUpdate::GetViewTranslations(void);
	GLboolean InputUpdate::GetViewUpdatePending(void);

	void InputUpdate::SetViewAngles(glm::vec2 value);
	void InputUpdate::SetViewTranslations(glm::vec3 value);
	void InputUpdate::SetViewUpdatePending(GLboolean value);
};

