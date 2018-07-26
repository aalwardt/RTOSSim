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

	//This maybe be changed to be shared by all schedulers, unless we find a reason for it not to be
	virtual void stateChangeRequest(Task* task, State state, long time) = 0;
};