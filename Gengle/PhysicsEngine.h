#pragma once
#include "GlobalTools.h"
#include "PhysicsDescriptor.h"

class PhysicsEngine
{
private:
	GLboolean isRunning = false;
	GLboolean resultsPending = false;
	GLboolean inputsPending = false;
	std::mutex mutex;
	std::thread* threadRunning = NULL;
	std::chrono::time_point<std::chrono::system_clock> clockStart;

	std::map<GUID, PhysicsDescriptor, GUIDComparer> physicsInputs;
	std::map<GUID, PhysicsDescriptor, GUIDComparer> physicsResults;

	GLboolean PhysicsEngine::GetIsRunning(void);

	void PhysicsEngine::Process(void);

	void PhysicsEngine::SetIsRunning(GLboolean value);

	void PhysicsEngine::StartRunning(void);
	void PhysicsEngine::StopRunning(void);
public:
	PhysicsEngine::PhysicsEngine(void);
	PhysicsEngine::~PhysicsEngine(void);

	std::map<GUID, PhysicsDescriptor, GUIDComparer> GetInputs(void);
	std::map<GUID, PhysicsDescriptor, GUIDComparer> GetResults(void);

	PhysicsDescriptor PhysicsEngine::ProcessItem(PhysicsDescriptor value);

	void PhysicsEngine::SetInputs(std::map<GUID, PhysicsDescriptor, GUIDComparer> items);
	void PhysicsEngine::SetResults(std::map<GUID, PhysicsDescriptor, GUIDComparer> items);
};

