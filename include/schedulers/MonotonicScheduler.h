#pragma once

#include "Scheduler.h"
#include "Simulator.h"
#include "TaskManager.h"
#include <queue>

template <class compare>
class MonotonicScheduler : public Scheduler {
	//Priority queue ordered by given binary predicate
	std::priority_queue<Task*, std::vector<Task*>, compare> readyQueue;
	Task* running;
public:
	MonotonicScheduler() : running(nullptr) { }
	void initialize();
	void dispatch(long time);
	void stateChangeRequest(Task* task, State state, long time);
};

//Binary predicate to order tasks by their period
struct periodCompare {
	bool operator() (Task* i, Task* j) {
		return (i->period > j->period);
	}
};
//Rate monotonic scheduling uses periods to order tasks
typedef MonotonicScheduler<periodCompare> RMScheduler;

//Binary predicate to order tasks by their deadline
struct deadlineCompare {
	bool operator() (Task* i, Task* j) {
		return (i->deadline > j->deadline);
	}
};
//Deadline monotonic scheduling uses deadlines to order tasks
typedef MonotonicScheduler<deadlineCompare> DMScheduler;

//---------------------------------------------
//Monotonic Scheduler Implementation
//Note, this must be in the header file to avoid compilation errors due to template
//---------------------------------------------

template <class compare>
void MonotonicScheduler<compare>::initialize() {
	//No functionality required
}

template <class compare>
void MonotonicScheduler<compare>::dispatch(long time) {
	compare comp;
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
template <class compare>
void MonotonicScheduler<compare>::stateChangeRequest(Task* task, State state, long time) {
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

