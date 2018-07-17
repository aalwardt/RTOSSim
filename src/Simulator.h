#pragma once

#include <map>
#include "SystemModel.h"


//Singleton class that runs the main simulation loop
class Simulator {
	//Constructor is private to ensure only one instance
	Simulator() {}

public:
	//Method to get only instance of the TaskManager
	static Simulator& getInstance() {
		static Simulator INSTANCE;
		return INSTANCE;
	}
	//Delete copy constructors to ensure no more instances of this class can be created
	Simulator(const Simulator&) = delete;
	void operator=(const Simulator&) = delete;

	//TimeAxis timeAxis;
	//SystemModel systemModel;
	//Scheduler scheduler;

	void start();
	void setup();
};

//A Job is an event on the TimeAxis
class Job {
	virtual void execute();
	virtual bool isDispatchNecessary();
};

class TimeAxis {
	std::map<Job, long> axis; //Mapping from Jobs to times

	void addJob();
	void removeJob();
	bool executeJobs();

	long getNextTimeStep();
};

class Scheduler {
	virtual void checkSystemModel();
	virtual void dispatch();
	//Name and description?
	virtual void initialize();
	virtual void releaseResource();
	virtual void requestResource();
	virtual void stateChangeRequest();
};

//Class used to store info on current Task such as state and execution time. Generates events.
class TaskMonitor {
	State state;
	long elapsedExecutionTime;

	void create();
	void makeReady();
	//If CREATED:	Just change to READY
	//If RUNNING:	Update elapsedExecutionTIme
	//				Remove any terminateJobEvents from TimeAxis
	//				Change to READY state
	void run();
	//Set to blocked
	//void block();
	void terminate();
	void remove();
};

//Singleton class used to map Tasks with their TaskMonitors
class TaskManager {
	std::map<Task, TaskMonitor> map;

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

	TaskMonitor& getMonitorForTask(Task t); //Returns TaskMonitor for a given Task, creates it if it does not already exist
};

