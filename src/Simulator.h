#pragma once

#include <map>
#include "SystemModel.h"


//Not sure this class is necessary?
class Simulator {
	TimeAxis timeAxis;
	SystemModel systemModel;
	Scheduler scheduler;

	long duration;

public:
	Simulator(SystemModel sm, Scheduler s, long duration) : systemModel(sm), scheduler(s), duration(duration) {};

	void start();
	void setup();
};

class TimeAxis {
	std::map<Job, long> axis; //Mapping from Jobs to times

	void addJob();
	void removeJob();
	bool executeJobs();

	long getNextTimeStep();
};

//A Job is an event on the TimeAxis
class Job {
	virtual void execute();
	virtual bool isDispatchNecessary();
};

class Scheduler {

	virtual void checkSystemModel();
	virtual void dispatch();
	//Name and string
	virtual void initialize();
	virtual void releaseResource();
	virtual void requestResource();
	virtual void stateChangeRequest();
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

	TaskMonitor getMonitorForTask(Task); //Returns TaskMonitor for a given Task, creates it if it does not already exist
};

//Class used to 
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