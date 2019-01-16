#pragma once
#include "GlobalTools.h"

enum MovementCommands : GLuint { MoveNone = 0, MoveForward = 1, MoveBackward = 2, MoveLeft = 4, MoveRight = 8, MoveUp = 16, MoveDown = 32 };
enum KeyStates : GLuint { KeyStateUp = 0, KeyStateDown = 1 };

inline MovementCommands operator|(MovementCommands a, MovementCommands b)
{
	return static_cast<MovementCommands>(static_cast<GLuint>(a) | static_cast<GLuint>(b));
}
inline MovementCommands operator&(MovementCommands a, MovementCommands b)
{
	return static_cast<MovementCommands>(static_cast<GLuint>(a) & static_cast<GLuint>(b));
}
inline MovementCommands operator~(MovementCommands a)
{
	return static_cast<MovementCommands>(~static_cast<GLuint>(a));
}

/// <summary>
/// Input update data
/// </summary>
/// <remarks>Input data from a user which may be relevant to render parameters/matrices</remarks>
class InputUpdate
{
private:
	GLboolean pendingViewUpdate = false;
	MovementCommands currentMovement = MoveNone;

	glm::vec2 viewAngles = glm::vec2(0.0, 0.0);
	glm::vec3 viewTranslations = glm::vec3(0.0, 0.0, 0.0);
public:
	InputUpdate::InputUpdate();
	InputUpdate::~InputUpdate();

	void InputUpdate::SetMovementFlag(MovementCommands flag, bool set);

	MovementCommands InputUpdate::GetMovementFlags(void);
	glm::vec2 InputUpdate::GetViewAngles(void);
	glm::vec3 InputUpdate::GetViewTranslations(void);
	GLboolean InputUpdate::GetViewUpdatePending(void);

	void InputUpdate::SetViewAngles(glm::vec2 value);
	void InputUpdate::SetViewTranslations(glm::vec3 value);
	void InputUpdate::SetViewUpdatePending(GLboolean value);
};

