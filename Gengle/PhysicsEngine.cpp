#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(void)
{
	this->StartRunning();
	return;
}

PhysicsEngine::~PhysicsEngine(void)
{
	this->StopRunning();
	return;
}

GLboolean PhysicsEngine::GetIsRunning(void)
{
	GLboolean value = false;
	this->mutex.lock();
	value = this->isRunning;
	this->mutex.unlock();
	return value;
}

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
		items = this->physicsInputs;
		// indicate inputs no longer pending
		this->inputsPending = false;
	}
	// unlock mutex
	this->mutex.unlock();
	// return results
	return items;
}

std::map<GUID, PhysicsDescriptor, GUIDComparer> PhysicsEngine::GetResults(void)
{
	// create empty results list
	std::map<GUID, PhysicsDescriptor, GUIDComparer> items;
	// lock mutex
	this->mutex.lock();
	// check if any results are pending
	if (this->resultsPending)
	{
		// if results pending, retrieve results
		items = this->physicsResults;
		// indicate results no longer pending
		this->resultsPending = false;
	}
	// unlock mutex
	this->mutex.unlock();
	// return results
	return items;
}

void PhysicsEngine::Process(void)
{
	while (this->GetIsRunning())
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end - this->clockStart;
		dprint("%f s\n", diff.count());
		std::map<GUID, PhysicsDescriptor, GUIDComparer> items = this->GetInputs();
		std::map<GUID, PhysicsDescriptor, GUIDComparer> results;
		for(std::map<GUID, PhysicsDescriptor, GUIDComparer>::iterator iterator = items.begin(); iterator != items.end(); iterator++)
		{
			PhysicsDescriptor result = this->ProcessItem(iterator->second);
			results.insert(std::make_pair(iterator->first, result));
		}
		this->SetResults(results);
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
	return;
}

PhysicsDescriptor PhysicsEngine::ProcessItem(PhysicsDescriptor value)
{
	PhysicsDescriptor result = value;
	result.Origin += value.Velocity;
	result.Velocity += value.Acceleration;
	return result;
}

void PhysicsEngine::SetIsRunning(GLboolean value)
{
	this->mutex.lock();
	this->isRunning = value;
	this->mutex.unlock();
	return;
}

void PhysicsEngine::SetInputs(std::map<GUID, PhysicsDescriptor, GUIDComparer> items)
{
	this->mutex.lock();
	this->physicsInputs = items;
	this->inputsPending = true;
	this->mutex.unlock();
	return;
}

void PhysicsEngine::SetResults(std::map<GUID, PhysicsDescriptor, GUIDComparer> items)
{
	this->mutex.lock();
	this->physicsResults = items;
	this->resultsPending = true;
	this->mutex.unlock();
	return;
}

void PhysicsEngine::StartRunning(void)
{
	if (this->GetIsRunning())
		return;
	this->clockStart = std::chrono::system_clock::now();
	this->SetIsRunning(true);
	this->threadRunning = new std::thread(&PhysicsEngine::Process, this);
	return;
}

void PhysicsEngine::StopRunning(void)
{
	if (!this->GetIsRunning())
		return;
	this->SetIsRunning(false);
	this->threadRunning->join();
	return;
}

