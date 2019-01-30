#pragma once
#include "GlobalTools.h"

struct PhysicsRectangle
{
private:
	glm::vec3 origin;
	glm::vec3 scale;
public:
	PhysicsRectangle::PhysicsRectangle(glm::vec3 origin_in, glm::vec3 scale_in);
	PhysicsRectangle::~PhysicsRectangle();

	GLfloat PhysicsRectangle::GetXMax(void);
	GLfloat PhysicsRectangle::GetXMin(void);
	GLfloat PhysicsRectangle::GetYMax(void);
	GLfloat PhysicsRectangle::GetYMin(void);
	GLfloat PhysicsRectangle::GetZMax(void);
	GLfloat PhysicsRectangle::GetZMin(void);
	GLboolean PhysicsRectangle::Intersects(PhysicsRectangle target);
};

