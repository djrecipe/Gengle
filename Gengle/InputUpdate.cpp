#include "InputUpdate.h"

#pragma region Instance Methods
/// <summary>
/// Create a new default input update object
/// </summary>
InputUpdate::InputUpdate()
{
}

/// <summary>
/// Destroy the input update object
/// </summary>
InputUpdate::~InputUpdate()
{
}

MovementCommands InputUpdate::GetMovementFlags(void)
{
	return this->currentMovement;
}

/// <summary>
/// Retrieve updated view/camera angles
/// </summary>
/// <returns>View angles</returns>
glm::vec2 InputUpdate::GetViewAngles(void)
{
	return this->viewAngles;
}

/// <summary>
/// Retrieve updated view/camera translations
/// </summary>
/// <returns>View translations</returns>
glm::vec3 InputUpdate::GetViewTranslations(void)
{
	return this->viewTranslations;
}

/// <summary>
/// Determine if a view update is pending
/// </summary>
/// <returns>True if a view update is pending, False otherwise</returns>
GLboolean InputUpdate::GetViewUpdatePending(void)
{
	return this->pendingViewUpdate;
}

void InputUpdate::SetMovementFlag(MovementCommands command, bool set)
{
	if (set)
	{
		this->currentMovement = this->currentMovement | command;
		dprint("Enabling movement.");
	}
	else
	{
		this->currentMovement = this->currentMovement & (~command);
		dprint("Disabling movement.");
	}
	return;
}

/// <summary>
/// Set updated view/camera angles
/// </summary>
/// <param name="value">View angles</param>
void InputUpdate::SetViewAngles(glm::vec2 value)
{
	this->viewAngles = value;
	return;
}

/// <summary>
/// Set a flag indicating that an update is available to the view matrix
/// </summary>
/// <param name="value"></param>
void InputUpdate::SetViewUpdatePending(GLboolean value)
{
	this->pendingViewUpdate = value;
	return;
}

/// <summary>
/// Set updated view/camera translations
/// </summary>
/// <param name="value">View translations</param>
void InputUpdate::SetViewTranslations(glm::vec3 value)
{
	this->viewTranslations = value;
	return;
}
#pragma endregion