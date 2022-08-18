#pragma once
#include "GlobalTools.h"
#include "PhysicsDescriptor.h"
class PhysicsEngine
{
private:
	GLboolean isRunning = false;
	GLboolean outputsPending = false;
	GLboolean inputsPending = false;
	std::thread* threadRunning = NULL;
	std::chrono::time_point<std::chrono::system_clock> clockStart;

	std::map<GUID, PhysicsDescriptor, GUIDComparer> inputs;
	std::map<GUID, PhysicsDescriptor, GUIDComparer> outputs;

	std::map<GUID, PhysicsDescriptor, GUIDComparer> GetInputs(void);
	GLboolean GetIsRunning(void);

	void Process(void);

	void SetIsRunning(GLboolean value);
	void SetOutputs(std::map<GUID, PhysicsDescriptor, GUIDComparer> items);

	void StartRunning(void);
	void StopRunning(void);
public:
	PhysicsEngine(void);
	~PhysicsEngine(void);

	std::map<GUID, PhysicsDescriptor, GUIDComparer> GetOutputs(void);

	PhysicsDescriptor ProcessItem(PhysicsDescriptor value, std::vector<PhysicsDescriptor> collisions);

	void SetInputs(std::map<GUID, PhysicsDescriptor, GUIDComparer> items);
};

