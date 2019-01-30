#include "PhysicsHitbox.h"

PhysicsHitbox::PhysicsHitbox(glm::vec3 size_in)
{
	this->size = size_in;
	return;
}

PhysicsHitbox::~PhysicsHitbox()
{
}

glm::vec3 PhysicsHitbox::GetSize(void)
{
	return this->size;
}
