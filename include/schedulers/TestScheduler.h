#pragma once

#include "Scheduler.h"

class TestScheduler: public Scheduler {
	Task* readyQueue; //Just a single task for now for testing
public:
	TestScheduler() : readyQueue(nullptr) { }
	void initialize();
	void dispatch(long time);
	void stateChangeRequest(Task* task, State state, long time);
};