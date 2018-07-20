#include "TaskManager.h"

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