#pragma once

#include "SystemModel.h"
#include <iostream>
#include <map>

//Class used to store info on current Task such as state and execution time. Generates events.
class TaskMonitor {
	State state;
	long absoluteDeadline;
	long executionStartTime;
	long elapsedExecutionTime;
public:

	TaskMonitor() :
		state(State::NON_EXISTING),
		absoluteDeadline(0),
		executionStartTime(0),
		elapsedExecutionTime(0)
	{}

	State getState() { return state; }

	void create(Task*, long time);
	void makeReady(Task*, long time);
	//If CREATED:	Just change to READY
	//If RUNNING:	Update elapsedExecutionTIme
	//				Remove any terminateJobEvents from TimeAxis
	//				Change to READY state
	void run(Task*, long time);
	//Set to blocked
	//void block();
	void terminate(Task*, long time);
	void remove(Task*, long time);
};

//Singleton class used to map Tasks with their TaskMonitors
class TaskManager {
	std::map<Task*, TaskMonitor*> map;

	TaskManager() {} //Constructor is private to ensure this is a singleton
public:
	//Method to get only instance of the TaskManager
	static TaskManager& getInstance() {
		static TaskManager INSTANCE;
		return INSTANCE;
	}
	//Delete copy constructors to ensure no more instances of this class can be created
	TaskManager(const TaskManager&) = delete;
	void operator=(const TaskManager&) = delete;

	//Returns TaskMonitor for a given Task, creates it if it does not already exist
	TaskMonitor* getMonitorForTask(Task* t) {
		if (map[t] == nullptr)
			map[t] = new TaskMonitor;
		return map[t];
	}
};