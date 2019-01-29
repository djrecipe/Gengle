#include "PhysicsDescriptor.h"

PhysicsDescriptor::PhysicsDescriptor(GUID id_in, glm::vec3 direction_in, glm::vec3 origin_in, GLdouble speed_in)
{
	this->id = id_in;
	this->direction = direction_in;
	this->origin = origin_in;
	this->speed = speed_in;
	return;
}

PhysicsDescriptor::~PhysicsDescriptor()
{
}


glm::vec3 PhysicsDescriptor::GetDirection(void)
{
	return this->direction;
}

GUID PhysicsDescriptor::GetID(void)
{
	return this->id;
}

glm::vec3 PhysicsDescriptor::GetOrigin(void)
{
	return this->origin;
}

GLdouble PhysicsDescriptor::GetSpeed(void)
{
	return this->speed;
}
