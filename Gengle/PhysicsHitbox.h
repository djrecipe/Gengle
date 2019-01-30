#pragma once
#include "GlobalTools.h"

class PhysicsHitbox
{
private:
	glm::vec3 size = glm::vec3(1.0,1.0,1.0);
public:
	PhysicsHitbox::PhysicsHitbox(glm::vec3 size_in);
	PhysicsHitbox::~PhysicsHitbox();

	glm::vec3 PhysicsHitbox::GetSize(void);
};

