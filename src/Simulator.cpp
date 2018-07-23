#include "Simulator.h"
#include <iostream>

void Simulator::setup() {
	//Initialize Scheduler
	scheduler->initialize();
	//Release first job of every task
	for (Task* t : systemModel.taskList) {
		Job * newJob = new TaskCreateJob(t);
		timeAxis.addJob(newJob, globalTime);
	}
}

//Run the main simulation loop
void Simulator::run() {
	bool running = true;
	bool dispatchNecessary;

	setup();

	while (running) {
		dispatchNecessary = timeAxis.executeJobs(globalTime);

		if (dispatchNecessary) {
			scheduler->dispatch(globalTime);
		}

		long nextTime = timeAxis.getNextTimeStep(globalTime);
		if (nextTime = LONG_MAX) {
			running = false;
		}

		globalTime = nextTime;
	}
}

void TimeAxis::addJob(Job* job, long time) {
	axis[time].push_front(job);
}	

void TimeAxis::removeJob(Job* job, long time) {
	axis[time].remove(job);
}

bool TimeAxis::executeJobs(long time) {
	//Get list from axis[time], iterate through every job there and execute()
	bool dispatchNecessary = false;
	auto list = axis[time];
	for (Job* job : list) {
		job->execute(time);
		dispatchNecessary = dispatchNecessary || job->isDispatchNecessary(); 
	}
	
	return dispatchNecessary;
}

long TimeAxis::getNextTimeStep(long time) {
	//Start iterator at element for current time
	auto it = axis.find(time);
	++it; //Increment iterator
	if (it != axis.end()) {
		//If it isn't the last element, return the new key (the next time)
		return (*it).first;
	}
	else { 
		//If it is the last element, return LONG_MAX
		return LONG_MAX;
	}
}