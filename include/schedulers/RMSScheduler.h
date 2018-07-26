#pragma once

#include "Scheduler.h"
#include <queue>

//Binary predicate to order tasks by their period
struct periodCompare {
	bool operator() (Task* i, Task* j) {
		return (i->period > j->period);
	}
};

class RMSScheduler : public Scheduler {
	//Priority queue ordered by task period
	std::priority_queue<Task*, std::vector<Task*>, periodCompare> readyQueue;
	Task* running;
public:
	RMSScheduler() : running(nullptr) { }
	void initialize();
	void dispatch(long time);
	void stateChangeRequest(Task* task, State state, long time);
};