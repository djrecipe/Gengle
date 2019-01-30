#pragma once
#include "GlobalTools.h"
#include "PhysicsDescriptor.h"

class PhysicsEngine
{
private:
	GLboolean isRunning = false;
	GLboolean outputsPending = false;
	GLboolean inputsPending = false;
	std::mutex mutex;
	std::thread* threadRunning = NULL;
	std::chrono::time_point<std::chrono::system_clock> clockStart;

	std::map<GUID, PhysicsDescriptor, GUIDComparer> inputs;
	std::map<GUID, PhysicsDescriptor, GUIDComparer> outputs;

	std::map<GUID, PhysicsDescriptor, GUIDComparer> GetInputs(void);
	GLboolean PhysicsEngine::GetIsRunning(void);

	void PhysicsEngine::Process(void);

	void PhysicsEngine::SetIsRunning(GLboolean value);
	void PhysicsEngine::SetOutputs(std::map<GUID, PhysicsDescriptor, GUIDComparer> items);

	void PhysicsEngine::StartRunning(void);
	void PhysicsEngine::StopRunning(void);
public:
	PhysicsEngine::PhysicsEngine(void);
	PhysicsEngine::~PhysicsEngine(void);

	std::map<GUID, PhysicsDescriptor, GUIDComparer> GetOutputs(void);

	PhysicsDescriptor PhysicsEngine::ProcessItem(PhysicsDescriptor value, std::vector<PhysicsDescriptor> collisions);

	void PhysicsEngine::SetInputs(std::map<GUID, PhysicsDescriptor, GUIDComparer> items);
};

