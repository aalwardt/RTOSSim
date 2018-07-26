#pragma once

#include <map>
#include <list>
#include "Scheduler.h"
#include "Jobs.h"
#include "SystemModel.h"

class TimeAxis {
	std::map<long, std::list<AxisEvent*>> axis; //Mapping from Jobs to times

public:
	void addJob(AxisEvent* job, long time);
	void removeJob(AxisEvent* job, long time);
	bool executeJobs(long time);

	long getNextTimeStep(long time);
};

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

