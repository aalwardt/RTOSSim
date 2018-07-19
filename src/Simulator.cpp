#include "Simulator.h"
#include <iostream>

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

long TimeAxis::getNextTimeStep(long time) {
	//Start iterator at element for current time
	auto it = axis.find(time);
	//If it's not the last element...
	if (it != axis.end()) {
		++it;				  //Increment iterator
		return (*it).first;	  //Return the key of the element (the next time)
	}
	else { 
		//If it is the last element, return LONG_MAX
		return LONG_MAX;
	}
}

void TaskMonitor::create(Task& t, long time) {
	//Set the absolute deadline of the task
	absoluteDeadline = time + t.deadline;
	state = State::CREATED;
	std::cout << "Task created." << time;
}

void TaskMonitor::makeReady(Task& t, long time) {
	//Update the execution time of the task if it was running
	if (state == RUNNING) {
		elapsedExecutionTime += time - executionStartTime;
		//TODO: Remove taskTerminateJob from TimeAxis
	}
	state = State::READY;
	std::cout << "Task ready." << time;
}

void TaskMonitor::run(Task& t, long time) {
	executionStartTime = time; //Set the execution time to start here
	int executionEndTime = time + t.executionTime - elapsedExecutionTime;
	state = State::RUNNING;
	//Add TaskTerminateJob at end of execution 
	Job * newJob = new TaskTerminateJob(t);
	Simulator::getInstance().timeAxis.addJob(newJob, executionEndTime);
	std::cout << "Task running." << time;
}

void TaskMonitor::terminate(Task& t, long time) {
	state = State::TERMINATED;
	std::cout << "Task terminated." << time;
}

void TaskMonitor::remove(Task& t, long time) {
	state = State::NON_EXISTING;
	std::cout << "Task removed." << time;
}