#pragma once

#include "SystemModel.h"

class Scheduler {
public:
	virtual void initialize() = 0;
	//virtual void checkSystemModel() = 0;
	virtual void dispatch(long time) = 0;
	//Name and description?
	//virtual void releaseResource() = 0;
	//virtual void requestResource() = 0;
	virtual void stateChangeRequest(Task* task, State state, long time) = 0;
};

class BasicScheduler: public Scheduler {
	Task* readyQueue; //Just a single task for now for testing
public:
	BasicScheduler() : readyQueue(nullptr) { }
	void initialize();
	void dispatch(long time);
	void stateChangeRequest(Task* task, State state, long time);
};