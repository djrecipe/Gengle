#pragma once
#include "GlobalTools.h"
#include "InputUpdate.h"

class MouseInputManager
{
private:
	InputUpdate * inputUpdate = NULL;
	glm::vec2 windowSize;
public:
	MouseInputManager::MouseInputManager(InputUpdate * input_update_in, glm::vec2 window_size);
	MouseInputManager::~MouseInputManager();
	void MouseInputManager::Process(int x, int y);
};

