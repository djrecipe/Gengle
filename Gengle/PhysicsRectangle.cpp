#include "Gengle.pch.h"
#include "PhysicsRectangle.h"

PhysicsRectangle::PhysicsRectangle(glm::vec3 origin_in, glm::vec3 scale_in)
{
	this->origin = origin_in;
	this->scale = scale_in;
	return;
}

PhysicsRectangle::~PhysicsRectangle()
{
}

GLfloat PhysicsRectangle::GetXMax(void)
{
	return this->origin.x + this->scale.x;
}

GLfloat PhysicsRectangle::GetXMin(void)
{
	return this->origin.x - this->scale.x;
}

GLfloat PhysicsRectangle::GetYMax(void)
{
	return this->origin.y + this->scale.y;
}

GLfloat PhysicsRectangle::GetYMin(void)
{
	return this->origin.y - this->scale.y;
}

GLfloat PhysicsRectangle::GetZMax(void)
{
	return this->origin.z + this->scale.z;
}

GLfloat PhysicsRectangle::GetZMin(void)
{
	return this->origin.z - this->scale.z;
}

GLboolean PhysicsRectangle::Intersects(PhysicsRectangle target)
{
	return this->GetXMin() < target.GetXMax() && this->GetXMax() > target.GetXMin() &&
		this->GetYMin() < target.GetYMax() && this->GetYMax() > target.GetYMin() &&
		this->GetXMin() < target.GetZMax() && this->GetZMax() > target.GetZMin();
}