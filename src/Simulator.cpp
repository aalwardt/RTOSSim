#include "Simulator.h"

void Simulator::setup() {
	//Initialize Scheduler
	scheduler->initialize();
	//Release first job of every task
	for (Task& t : systemModel.taskList) {
		Job * newJob = new TaskCreateJob(t);
		timeAxis.addJob(newJob, globalTime);
	}
}

//Run the main simulation loop
void Simulator::run() {
	setup();
	
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