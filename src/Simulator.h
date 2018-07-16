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

class TaskManager {
	std::map<Task, TaskMonitor> map;

	TaskMonitor getMonitorForTask(Task);
};

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