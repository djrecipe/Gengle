#include "PhysicsEngine.h"

#pragma region Instance Methods
/// <summary>
/// Create a new physics engine
/// </summary>
PhysicsEngine::PhysicsEngine(void)
{
	this->StartRunning();
	return;
}

/// <summary>
/// Destroy the physics engine
/// </summary>
PhysicsEngine::~PhysicsEngine(void)
{
	this->StopRunning();
	return;
}

/// <summary>
/// Gets a boolean value indicating whether or not the engine is running
/// </summary>
/// <remarks>Thread-safe using a shared mutex</remarks>
/// <returns>True if the physics engine is running, False otherwise</returns>
GLboolean PhysicsEngine::GetIsRunning(void)
{
	GLboolean value = false;
	this->mutex.lock();
	value = this->isRunning;
	this->mutex.unlock();
	return value;
}

/// <summary>
/// Gets a list of entities acting as inputs to the physics engine
/// </summary>
/// <remarks>Thread-safe using a shared mutex</remarks>
/// <returns>List of physics entities prior to being updated by the physics engine</returns>
std::map<GUID, PhysicsDescriptor, GUIDComparer> PhysicsEngine::GetInputs(void)
{
	// create empty inputs list
	std::map<GUID, PhysicsDescriptor, GUIDComparer> items;
	// lock mutex
	this->mutex.lock();
	// check if any inputs are pending
	if (this->inputsPending)
	{
		// if results pending, retrieve results
		items = this->inputs;
		// indicate inputs no longer pending
		this->inputsPending = false;
	}
	// unlock mutex
	this->mutex.unlock();
	// return results
	return items;
}

/// <summary>
/// Gets a list of entities acting as outputs from the physics engine
/// </summary>
/// <remarks>Thread-safe using a shared mutex</remarks>
/// <returns>List of physics entities after being updated by the physics engine</returns>
std::map<GUID, PhysicsDescriptor, GUIDComparer> PhysicsEngine::GetOutputs(void)
{
	// create empty results list
	std::map<GUID, PhysicsDescriptor, GUIDComparer> items;
	// lock mutex
	this->mutex.lock();
	// check if any results are pending
	if (this->outputsPending)
	{
		// if results pending, retrieve results
		items = this->outputs;
		// indicate results no longer pending
		this->outputsPending = false;
	}
	// unlock mutex
	this->mutex.unlock();
	// return results
	return items;
}

/// <summary>
/// Process all pending physics operations
/// </summary>
/// <remarks>Loops as long as the physics engine is running</remarks>
void PhysicsEngine::Process(void)
{
	while (this->GetIsRunning())
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end - this->clockStart;
		//dprint("%f s\n", diff.count());
		std::map<GUID, PhysicsDescriptor, GUIDComparer> items = this->GetInputs();
		std::map<GUID, PhysicsDescriptor, GUIDComparer> results;
		for(std::map<GUID, PhysicsDescriptor, GUIDComparer>::iterator iterator = items.begin();
			iterator != items.end(); iterator++)
		{
			// loop through remaining items to find collisions
			std::vector<PhysicsDescriptor> collisions;
			for (std::map<GUID, PhysicsDescriptor, GUIDComparer>::iterator collision_iterator = items.begin();
				collision_iterator != items.end(); collision_iterator++)
			{
				// skip collision check for identical entities
				if (iterator->second.GetID() == collision_iterator->second.GetID())
					continue;
				// calculate distance between entities
				PhysicsRectangle rect1 = iterator->second.GetHitbox();
				PhysicsRectangle rect2 = collision_iterator->second.GetHitbox();
				if (rect1.Intersects(rect2))
				{
					dprint("%f collision detected\n", diff.count());
					collisions.push_back(collision_iterator->second);
				}
			}
			// process physics for single entity
			iterator->second = this->ProcessItem(iterator->second, collisions);
			results.insert(std::make_pair(iterator->first, iterator->second));
		}
		this->SetOutputs(results);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return;
}

/// <summary>
/// Process a single physics entity
/// </summary>
/// <param name="value">Physical properties of entity to process</param>
/// <returns>Resulting physical properties after one tick of time</returns>
PhysicsDescriptor PhysicsEngine::ProcessItem(PhysicsDescriptor value, std::vector<PhysicsDescriptor> collisions)
{
	PhysicsDescriptor result = value;
	result.Origin += value.Velocity;
	result.Velocity += value.Acceleration;
	return result;
}

/// <summary>
/// Sets a boolean value indicating whether or not the engine is running
/// </summary>
/// <param name="value">True if the engine is running, False otherwise</param>
/// <remarks>Thread-safe using a shared mutex</remarks>
void PhysicsEngine::SetIsRunning(GLboolean value)
{
	this->mutex.lock();
	this->isRunning = value;
	this->mutex.unlock();
	return;
}

/// <summary>
/// Sets a list of entities acting as inputs to the physics engine
/// </summary>
/// <param name="items">List of physics entities prior to being updated by the physics engine</param>
/// <remarks>Thread-safe using a shared mutex</remarks>
void PhysicsEngine::SetInputs(std::map<GUID, PhysicsDescriptor, GUIDComparer> items)
{
	this->mutex.lock();
	this->inputs = items;
	this->inputsPending = true;
	this->mutex.unlock();
	return;
}

/// <summary>
/// Sets a list of entities acting as outputs from the physics engine
/// </summary>
/// <param name="items">List of physics entities after being updated by the physics engine</param>
/// <remarks>Thread-safe using a shared mutex</remarks>
void PhysicsEngine::SetOutputs(std::map<GUID, PhysicsDescriptor, GUIDComparer> items)
{
	this->mutex.lock();
	this->outputs = items;
	this->outputsPending = true;
	this->mutex.unlock();
	return;
}

/// <summary>
/// Start the physics engine
/// </summary>
/// <remarks>Starts the physics engine loop on a background thread</remarks>
void PhysicsEngine::StartRunning(void)
{
	if (this->GetIsRunning())
		return;
	this->clockStart = std::chrono::system_clock::now();
	this->SetIsRunning(true);
	this->threadRunning = new std::thread(&PhysicsEngine::Process, this);
	return;
}

/// <summary>
/// Stop the physics engine
/// </summary>
/// <remarks>Terminates the physics engine loop and joins the background thread</remarks>
void PhysicsEngine::StopRunning(void)
{
	if (!this->GetIsRunning())
		return;
	this->SetIsRunning(false);
	this->threadRunning->join();
	return;
}
#pragma endregion

