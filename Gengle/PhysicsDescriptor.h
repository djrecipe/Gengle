#pragma once
#include "GlobalTools.h"

struct PhysicsDescriptor
{
private:
	GUID id;
	glm::vec3 direction;
	glm::vec3 origin;
	GLdouble speed;
public:
	PhysicsDescriptor::PhysicsDescriptor(GUID id_in, glm::vec3 direction_in, glm::vec3 origin_in, GLdouble speed_in);
	PhysicsDescriptor::~PhysicsDescriptor();

	glm::vec3 PhysicsDescriptor::GetDirection(void);
	GUID PhysicsDescriptor::GetID(void);
	glm::vec3 PhysicsDescriptor::GetOrigin(void);
	GLdouble PhysicsDescriptor::GetSpeed(void);
};

