#pragma once

#include "SystemModel.h"
#include "TaskManager.h"

class Scheduler {
public:
	virtual void initialize() = 0;
	//virtual void checkSystemModel() = 0;
	virtual void dispatch(long time) = 0;
	//Name and description?
	//virtual void releaseResource() = 0;
	//virtual void requestResource() = 0;
	virtual void stateChangeRequest(Task& task, State state, long time) = 0;
};

class BasicScheduler : public Scheduler {
	Task* readyQueue; //Just a single task for now for testing
public:
	void initialize() {
		//Do nothing
	}
	void dispatch(long time) {
		//Select one ready task (This basic scheduler will just select the first one)
		Task* readyTask = readyQueue;
		stateChangeRequest(*readyTask, State::RUNNING, time);
	}
	void stateChangeRequest(Task& task, State state, long time) {
		//Get monitor for the task
		TaskMonitor monitor = TaskManager::getInstance().getMonitorForTask(task);

		switch (state) {
		case NON_EXISTING:
			if (monitor.getState() == TERMINATED)
				monitor.remove(task, time);
			break;
		case CREATED:
			if (monitor.getState() == NON_EXISTING) {
				monitor.create(task, time);
				//Immediately make it ready
				stateChangeRequest(task, State::READY, time);
			}
			break;
		case READY:
			if (monitor.getState() == CREATED)
				monitor.makeReady(task, time);
			else if (monitor.getState() == RUNNING)
				monitor.makeReady(task, time); //TODO: Logic for storing execution time
			//Move it into the ready queue
			readyQueue = &task;
			break;
		case RUNNING:
			if (monitor.getState() == READY)
				monitor.run(task, time);
			break;
			//case BLOCKED:
		case TERMINATED:
			if (monitor.getState() == RUNNING) {
				monitor.terminate(task, time);
				stateChangeRequest(task, State::NON_EXISTING, time);
			}
		}

	}
};