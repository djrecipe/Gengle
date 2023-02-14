#pragma once
#include "PhysicsRectangle.h"

/// <summary>
/// Entity physics properties
/// </summary>
struct PhysicsDescriptor
{
private:
	GUID id;
public:
	glm::vec3 Acceleration = glm::vec3(0.0);
	glm::vec3 Origin = glm::vec3(0.0);
	glm::vec3 Size = glm::vec3(1.0);
	glm::vec3 Velocity = glm::vec3(0.0);

	GLfloat Mass = 1.0;

	PhysicsDescriptor& operator=(const PhysicsDescriptor &object);

	PhysicsDescriptor(void);
	PhysicsDescriptor(GUID id_in);
	~PhysicsDescriptor();

	PhysicsRectangle GetHitbox(void);
	GUID GetID(void);
	void SetID(GUID id_in);
};

