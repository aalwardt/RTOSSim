#pragma once

#include <vector>

enum State {
	NON_EXISTING,
	CREATED,
	READY,
	RUNNING,
	BLOCKED,
	TERMINATED
};

enum Periodity {
	PERIODIC,
	SPORADIC
};

struct Task {
	//Deadline Type: HARD or SOFT
	int deadline;
	int priority;
	//int offset;
	Periodity periodity;
	int period;
	//int jitter;
	//int contextSwitchingTime;
	int executionTime;
	//int responseTime;

	//TODO: Resource usage

	//TODO: Commands for tasks with multiple execution and resource acquisition block
	//For now we will model this with just a single execution time

	//Default constructor
	Task() : ID(newID++) {}
	int getID() { return ID; }

	//Ensure that Task objects are not copied. All task instances should be stored in the system model
	Task(const Task&) = delete;
	void operator=(const Task&) = delete;

	//Comparison operation
	//Tasks are ordered by their priority, with lower numbers being higher priority
private:
	static int newID; //Keep track of task ID numbers
	const int ID; //Id number
};

struct Core {
	bool active;
	Core() : active(true) {}
};

class SystemModel {
public:
	std::vector<Task*> taskList;
	//For now, we will assume all cores are homogeneous
	//And just model the number of cores
	//std::vector<Core*> coreList;
	int numCores;

	//Default constructor
	SystemModel(int cores) : numCores(cores) {}
};

