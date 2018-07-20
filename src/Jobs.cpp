#include "Jobs.h"
#include "Simulator.h"
#include "Scheduler.h"

void TaskCreateJob::execute(long time) {
	Simulator::getInstance().scheduler->stateChangeRequest(task, State::CREATED, time);
}

void TaskTerminateJob::execute(long time) {
	Simulator::getInstance().scheduler->stateChangeRequest(task, State::TERMINATED, time);
}