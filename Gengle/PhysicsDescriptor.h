#pragma once
#include "GlobalTools.h"

#include "PhysicsRectangle.h"

/// <summary>
/// Entity physics properties
/// </summary>
struct PhysicsDescriptor
{
private:
	GUID id;
public:
	GLboolean Enabled = true;

	glm::vec3 Acceleration = glm::vec3(0.0);
	glm::vec3 Origin = glm::vec3(0.0);
	glm::vec3 Size = glm::vec3(1.0);
	glm::vec3 Velocity = glm::vec3(0.0);

	GLfloat Mass = 1.0;

	PhysicsDescriptor& PhysicsDescriptor::operator=(const PhysicsDescriptor &object);

	PhysicsDescriptor::PhysicsDescriptor(void);
	PhysicsDescriptor::PhysicsDescriptor(GUID id_in);
	PhysicsDescriptor::~PhysicsDescriptor();

	PhysicsRectangle PhysicsDescriptor::GetHitbox(void);
	GUID PhysicsDescriptor::GetID(void);
	void PhysicsDescriptor::SetID(GUID id_in);
};

