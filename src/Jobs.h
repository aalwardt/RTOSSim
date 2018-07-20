#pragma once

#include "SystemModel.h"

//A Job is an event on the TimeAxis
class Job {
protected:
	Task& task;
public:
	Job(Task& t) : task(t) {}
	virtual void execute(long time) = 0;
	virtual bool isDispatchNecessary() = 0;
};

class TaskCreateJob : public Job {
public:
	TaskCreateJob(Task& t) : Job(t) {}
	void execute(long time);
	bool isDispatchNecessary() { return true; }
};

class TaskTerminateJob : public Job {
public:
	TaskTerminateJob(Task& t) : Job(t) {}
	void execute(long time);
	bool isDispatchNecessary() { return true; }
};