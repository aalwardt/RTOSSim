#pragma once

#include <map>
#include <list>
#include "SystemModel.h"
#include "Scheduler.h"
#include "Jobs.h"


//Singleton class that runs the main simulation loop
class Simulator {
	long globalTime;
	//Constructor is private to ensure only one instance
	Simulator() : globalTime(0) {}

public:
	//Method to get only instance of the TaskManager
	static Simulator& getInstance() {
		static Simulator INSTANCE;
		return INSTANCE;
	}
	//Delete copy constructors to ensure no more instances of this class can be created
	Simulator(const Simulator&) = delete;
	void operator=(const Simulator&) = delete;

	SystemModel systemModel;
	TimeAxis timeAxis;
	Scheduler* scheduler;

	void run();
	void setup();
};

class TimeAxis {
	std::map<long, std::list<Job*>> axis; //Mapping from Jobs to times

public:
	void addJob(Job* job, long time);
	void removeJob(Job* job, long time);
	bool executeJobs(long time);

	long getNextTimeStep();
};

//Class used to store info on current Task such as state and execution time. Generates events.
class TaskMonitor {
	State state;
	long elapsedExecutionTime;
public:

	TaskMonitor() :
		state(NON_EXISTING),
		elapsedExecutionTime(0)
	{}

	State getState() { return state; }

	void create(Task&);
	void makeReady(Task&);
	//If CREATED:	Just change to READY
	//If RUNNING:	Update elapsedExecutionTIme
	//				Remove any terminateJobEvents from TimeAxis
	//				Change to READY state
	void run(Task&);
	//Set to blocked
	//void block();
	void terminate(Task&);
	void remove(Task&);
};

//Singleton class used to map Tasks with their TaskMonitors
class TaskManager {
	std::map<Task&, TaskMonitor> map;

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
	TaskMonitor& getMonitorForTask(Task& t) { return map[t]; }

	//Returns a list of tasks which are in the ready state
	std::list<Task> getReadyTasks() {
		std::list<Task> taskList;
		for (auto pair : map)
			if (pair.second.getState() == READY)
				taskList.push_back(pair.first);

		return taskList;
	}
};

