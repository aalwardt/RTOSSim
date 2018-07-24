#include "TaskManager.h"
#include "Jobs.h"
#include "Simulator.h"
#include <iostream>

void TaskMonitor::create(Task* t, long time) {
	//Set the absolute deadline of the task
	absoluteDeadline = time + t->deadline;
	state = State::CREATED;
	std::cout << time << '\t' << t << "\tTask created\n";
	//If task is periodic, add new task creation event for next release
	if (t->periodity == PERIODIC) {
		Job * newJob = new TaskCreateJob(t);
		Simulator::getInstance().timeAxis.addJob(newJob, time + t->period);
	}
}

void TaskMonitor::makeReady(Task* t, long time) {
	//Update the execution time of the task if it was running
	if (state == RUNNING) {
		elapsedExecutionTime += time - executionStartTime;
		//TODO: Remove taskTerminateJob from TimeAxis
	}
	state = State::READY;
	std::cout << time << '\t' << t << "\tTask ready\n";
}

void TaskMonitor::run(Task* t, long time) {
	executionStartTime = time; //Set the execution time to start here
	int executionEndTime = time + t->executionTime - elapsedExecutionTime;
	state = State::RUNNING;
	//Add TaskTerminateJob at end of execution 
	Job * newJob = new TaskTerminateJob(t);
	Simulator::getInstance().timeAxis.addJob(newJob, executionEndTime);
	std::cout << time << '\t' << t << "\tTask running\n";
}

void TaskMonitor::terminate(Task* t, long time) {
	state = State::TERMINATED;
	std::cout << time << '\t' << t << "\tTask terminated\n";
}

void TaskMonitor::remove(Task* t, long time) {
	state = State::NON_EXISTING;
	std::cout << time << '\t' << t << "\tTask removed\n";
}