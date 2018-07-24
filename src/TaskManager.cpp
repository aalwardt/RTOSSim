#include "TaskManager.h"
#include "Jobs.h"
#include "Simulator.h"
#include <iostream>

void TaskMonitor::create(Task* t, long time) {
	//Only create a task if it doesn't already exist
	if (state == NON_EXISTING) {
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
	else {
		//TODO: Throw exception?
	}
}

void TaskMonitor::makeReady(Task* t, long time) {
	//Only make ready if the task is RUNNING or CREATED
	switch (state) {
	case RUNNING:
		//If already running, update the elapsed execution time
		elapsedExecutionTime += time - executionStartTime;
	case CREATED:
		state = READY;
		std::cout << time << '\t' << t << "\tTask ready\n";
		break;
	default:
		//TODO: Throw exception?
		break;
	}
}

void TaskMonitor::run(Task* t, long time) {
	//Only run a task if it's ready
	if (state == READY) {
		executionStartTime = time; //Set the execution time to start here
		int executionEndTime = time + t->executionTime - elapsedExecutionTime;
		state = State::RUNNING;

		//Add TaskTerminateJob at end of execution 
		Job * newJob = new TaskTerminateJob(t);
		Simulator::getInstance().timeAxis.addJob(newJob, executionEndTime);

		std::cout << time << '\t' << t << "\tTask running\n";
	}
	else {
		//TODO: Throw exception?
	}
}

void TaskMonitor::terminate(Task* t, long time) {
	//Only terminate a task that is running (it's execution has finished)
	if (state == RUNNING) {
		state = State::TERMINATED;
		std::cout << time << '\t' << t << "\tTask terminated\n";
	}
	else {
		//TODO: Throw exception?
	}
}

void TaskMonitor::remove(Task* t, long time) {
	//Only remove tasks that have been terminated
	if (state == TERMINATED) {
		state = State::NON_EXISTING;
		std::cout << time << '\t' << t << "\tTask removed\n";
	}
	else {
		//TODO: Throw exception?
	}
}