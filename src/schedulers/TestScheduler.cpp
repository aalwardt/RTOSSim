#include "TestScheduler.h"
#include "TaskManager.h"
#include <iostream>

void TestScheduler::initialize() {
	//Do nothing
}
void TestScheduler::dispatch(long time) {
	//Select one ready task (This basic scheduler will just select the first one)
	Task* readyTask = readyQueue;
	stateChangeRequest(readyTask, State::RUNNING, time);
}
void TestScheduler::stateChangeRequest(Task* task, State state, long time) {
	//std::cout << "State Change Request for task: " << task << std::endl;
	//Get monitor for the task
	TaskMonitor* monitor = TaskManager::getInstance().getMonitorForTask(task);
	//std::cout << "Monitor for task: " << &monitor << std::endl;


	//TODO: Move state transition enforcement into TaskMonitor
	//Throw exceptions when it fails?
	switch (state) {
	case NON_EXISTING:
		monitor->remove(task, time);
		break;
	case CREATED:
		monitor->create(task, time);
		stateChangeRequest(task, READY, time);
		break;
	case READY:
		monitor->makeReady(task, time);
		readyQueue = task; //Put our task into the ready queue (only one ready task in this dirty example)
		break;
	case RUNNING:
		monitor->run(task, time);
		break;
		//case BLOCKED:
	case TERMINATED:
		monitor->terminate(task, time);
		stateChangeRequest(task, NON_EXISTING, time);
		break;
	}
}