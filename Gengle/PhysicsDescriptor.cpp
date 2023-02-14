#include "Gengle.pch.h"
#include "PhysicsDescriptor.h"

#pragma region Instance Methods
/// <summary>
/// Equals operator override
/// </summary>
/// <param name="object">Right-hand side source object to copy</param>
/// <returns>A copy of the specified physics object</returns>
/// <remarks>Does not copy unique GUID of the source object</remarks>
PhysicsDescriptor& PhysicsDescriptor::operator=(const PhysicsDescriptor &object)
{
	this->Acceleration = object.Acceleration;
	this->Origin = object.Origin;
	this->Velocity = object.Velocity;
	return *this;
}

/// <summary>
/// Create a new physics descriptor
/// </summary>
/// <remarks>This physics descriptor is invalid until the GUID is set</remarks>
PhysicsDescriptor::PhysicsDescriptor(void)
{
	return;
}

/// <summary>
/// Create a new physics descriptor using the specified GUID
/// </summary>
/// <param name="id_in">Unique identifier</param>
PhysicsDescriptor::PhysicsDescriptor(GUID id_in)
{
	this->id = id_in;
	return;
}

/// <summary>
/// Destroy the physics descriptor
/// </summary>
PhysicsDescriptor::~PhysicsDescriptor()
{
}

PhysicsRectangle PhysicsDescriptor::GetHitbox(void)
{
	return PhysicsRectangle(this->Origin, this->Size);
}

/// <summary>
/// Gets the unique identifier of the physics descriptor
/// </summary>
/// <returns>Unique identifier</returns>
GUID PhysicsDescriptor::GetID(void)
{
	if (this->id == GUID_NULL)
		throw new std::runtime_error("Error while retrieving physics descriptor ID (value is uninitialized)");
	return this->id;
}

/// <summary>
/// Sets the unique identifier of the physics descriptor
/// </summary>
/// <param name="id_in"></param>
void PhysicsDescriptor::SetID(GUID id_in)
{
	this->id = id_in;
	return;
}
#pragma endregion
