#pragma once

#include "Scheduler.h"
#include "TaskManager.h"
#include <vector>
#include <algorithm>

//Single core scheduling algorithm
class EDFScheduler : public Scheduler {
	std::vector<Task*> readyQueue;
	Task* running;
public:
	EDFScheduler() : running(nullptr) { }
	void initialize();
	void dispatch(long time);
	void stateChangeRequest(Task* task, State state, long time);
};

void EDFScheduler::initialize() {
	//No initialization needed
}

//Sorts tasks with the closer absolute deadline to the front of the queue
struct absoluteDeadlineCompare {
	bool operator() (Task* i, Task* j) {
		TaskMonitor* monitor_i = TaskManager::getInstance().getMonitorForTask(i);
		TaskMonitor* monitor_j = TaskManager::getInstance().getMonitorForTask(j);
		return (monitor_i->getAbsoluteDeadline() > monitor_j->getAbsoluteDeadline());
	}
};

void EDFScheduler::dispatch(long time) {
	absoluteDeadlineCompare comp;
	//If the queue is not empty
	if (!readyQueue.empty()) {
		//Order the ready tasks by earliest deadline first
		//This is done at every scheduling because these change as tasks change states
		std::sort(readyQueue.begin(), readyQueue.end(), absoluteDeadlineCompare);
		//If nothing is running, just run it
		if (running == nullptr) {
			//Pull the task from the top of the ready queue and make it run
			stateChangeRequest(readyQueue.front(), RUNNING, time);
			running = readyQueue.front();
			readyQueue.erase(readyQueue.begin());
		}
		//If element at top of queue is higher priority than running
		else if (comp(running, readyQueue.front())) {
			//Stop the current task from running
			stateChangeRequest(running, READY, time);
			//Pull the task from the top of the ready queue and make it run
			stateChangeRequest(readyQueue.front(), RUNNING, time);
			running = readyQueue.front();
			readyQueue.erase(readyQueue.begin());
		}
	}
}

void EDFScheduler::stateChangeRequest(Task* task, State state, long time) {
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
		readyQueue.push_back(task);
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
