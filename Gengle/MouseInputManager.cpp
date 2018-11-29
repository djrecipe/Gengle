#include "GlutManager.h"
#include "MouseInputManager.h"

MouseInputManager::MouseInputManager(InputUpdate * input_update_in, glm::vec2 window_size)
{
	this->inputUpdate = input_update_in;
	this->windowSize = window_size;
	return;
}


MouseInputManager::~MouseInputManager()
{
}

void MouseInputManager::Process(int x, int y)
{
	int width_half = this->windowSize[0] / 2;
	int height_half = this->windowSize[1] / 2;
	if (x == width_half && y == height_half)
		return;


	GLfloat angle_up = this->inputUpdate->GetAngleUp();
	GLfloat angle_side = this->inputUpdate->GetAngleSide();

	this->inputUpdate->AddVerticalAngle(y - height_half);
	this->inputUpdate->AddHorizontalAngle(x - width_half);

	//dprint("Processing Mouse ::: x: %f | y: %f", this->inputUpdate->GetAngleSide(), this->inputUpdate->GetAngleUp());

	glutWarpPointer(width_half, height_half);
	glutPostRedisplay();
	return;
}

