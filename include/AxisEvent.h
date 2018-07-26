#pragma once

#include "SystemModel.h"

//An AxisEvent is an event on the TimeAxis
class AxisEvent {
protected:
	Task* task;
public:
	AxisEvent(Task* t) : task(t) {}
	virtual void execute(long time) = 0;
	virtual bool isDispatchNecessary() = 0;
};

class TaskCreateEvent : public AxisEvent {
public:
	TaskCreateEvent(Task* t) : AxisEvent(t) {}
	void execute(long time);
	bool isDispatchNecessary() { return true; }
};

class TaskTerminateEvent : public AxisEvent {
public:
	TaskTerminateEvent(Task* t) : AxisEvent(t) {}
	void execute(long time);
	bool isDispatchNecessary() { return true; }
};