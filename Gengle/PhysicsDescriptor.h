#pragma once
#include "GlobalTools.h"

struct PhysicsDescriptor
{
private:
	GUID id;
public:
	glm::vec3 Acceleration = glm::vec3(0.0);
	glm::vec3 Origin = glm::vec3(0.0);
	glm::vec3 Velocity = glm::vec3(0.0);

	PhysicsDescriptor& PhysicsDescriptor::operator=(const PhysicsDescriptor &object);

	PhysicsDescriptor::PhysicsDescriptor(void);
	PhysicsDescriptor::PhysicsDescriptor(GUID id_in);
	PhysicsDescriptor::PhysicsDescriptor(GUID id_in, glm::vec3 origin_in, glm::vec3 velocity_in, glm::vec3 acceleration_in);
	PhysicsDescriptor::~PhysicsDescriptor();

	GUID PhysicsDescriptor::GetID(void);
	void PhysicsDescriptor::SetID(GUID id_in);
};

