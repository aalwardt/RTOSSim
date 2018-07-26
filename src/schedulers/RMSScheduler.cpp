#include "RMSScheduler.h"
#include "Simulator.h"
#include "TaskManager.h"

void RMSScheduler::initialize() {
	//No functionality required
}

void RMSScheduler::dispatch(long time) {
	periodCompare comp;
	//If the queue is not empty
	if (!readyQueue.empty()) {
		//If nothing is running, just run it
		if (running == nullptr) {
			//Pull the task from the top of the ready queue and make it run
			stateChangeRequest(readyQueue.top(), RUNNING, time);
			running = readyQueue.top();
			readyQueue.pop();
		}
		//If element at top of queue is higher priority than running
		else if (comp(running, readyQueue.top())) {
			//Stop the current task from running
			stateChangeRequest(running, READY, time);
			//Pull the task from the top of the ready queue and make it run
			stateChangeRequest(readyQueue.top(), RUNNING, time);
			running = readyQueue.top();
			readyQueue.pop();
		}
	}

}

void RMSScheduler::stateChangeRequest(Task* task, State state, long time) {
	//Get monitor for the task
	TaskMonitor* monitor = TaskManager::getInstance().getMonitorForTask(task);

	switch (state) {
	case NON_EXISTING:
		monitor->remove(task, time);
		break;
	case CREATED:
		monitor->create(task, time);
		//Immediately make it READY
		stateChangeRequest(task, READY, time);
		break;
	case READY:
		monitor->makeReady(task, time);
		//Move the task into the ready queue
		readyQueue.push(task);
		break;
	case RUNNING:
		monitor->run(task, time);
		break;
		//case BLOCKED:
	case TERMINATED:
		monitor->terminate(task, time);
		//Update running pointer
		running = nullptr;
		//Immediately make it NON_EXISTING
		stateChangeRequest(task, NON_EXISTING, time);
		break;
	}
}