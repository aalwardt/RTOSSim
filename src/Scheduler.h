#include "SystemModel.h"

class Scheduler {
public:
	virtual void initialize() = 0;
	//virtual void checkSystemModel() = 0;
	virtual void dispatch(long time) = 0;
	//Name and description?
	//virtual void releaseResource() = 0;
	//virtual void requestResource() = 0;
	virtual void stateChangeRequest(Task task, State state, long time) = 0;
};

class BasicScheduler : public Scheduler {
	void initialize() {
		//Do nothing
	}
	void dispatch(long time) {
		//Select one ready task (This basic scheduler will just select the first one)
		Task readyTask = TaskManager::getInstance().getReadyTasks().front;
		stateChangeRequest(readyTask, State::RUNNING, time);
	}
	void stateChangeRequest(Task& task, State state, long time) {
		//Get monitor for the task
		TaskMonitor monitor = TaskManager::getInstance().getMonitorForTask(task);

		switch (state) {
		case NON_EXISTING:
			if (monitor.getState() == TERMINATED)
				monitor.remove(task);
			break;
		case CREATED:
			if (monitor.getState() == NON_EXISTING) {
				monitor.create(task);
				//Immediately make it ready
				stateChangeRequest(task, State::READY, time);
			}
			break;
		case READY:
			if (monitor.getState() == CREATED)
				monitor.makeReady(task);
			else if (monitor.getState == RUNNING)
				monitor.makeReady(task); //TODO: Logic for storing execution time
			break;
		case RUNNING:
			if (monitor.getState() == READY)
				monitor.run(task);
			break;
			//case BLOCKED:
		case TERMINATED:
			if (monitor.getState() == RUNNING)
				monitor.terminate(task);
		}

	}
};