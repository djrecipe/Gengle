#include "PhysicsDescriptor.h"

PhysicsDescriptor& PhysicsDescriptor::operator=(const PhysicsDescriptor &object)
{
	this->Acceleration = object.Acceleration;
	this->Origin = object.Origin;
	this->Velocity = object.Velocity;
	return *this;
}

PhysicsDescriptor::PhysicsDescriptor(void)
{
	return;
}

PhysicsDescriptor::PhysicsDescriptor(GUID id_in)
{
	this->id = id_in;
	return;
}

PhysicsDescriptor::PhysicsDescriptor(GUID id_in, glm::vec3 origin_in, glm::vec3 velocity_in, glm::vec3 acceleration_in)
{
	this->Acceleration = acceleration_in;
	this->id = id_in;
	this->Origin = origin_in;
	this->Velocity = velocity_in;
	return;
}

PhysicsDescriptor::~PhysicsDescriptor()
{
}

GUID PhysicsDescriptor::GetID(void)
{
	if (this->id == GUID_NULL)
		throw new std::runtime_error("Error while retrieving physics descriptor ID (value is uninitialized)");
	return this->id;
}

void PhysicsDescriptor::SetID(GUID id_in)
{
	this->id = id_in;
	return;
}
