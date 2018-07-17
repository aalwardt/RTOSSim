#include "Jobs.h"
#include "SystemModel.h"

void TaskCreateJob::execute(long time) {
	Simulator::getInstance().scheduler.stateChangeRequest(task, State::CREATED, time);
}

void TaskTerminateJob::execute(long time) {
	Simulator::getInstance().scheduler.stateChangeRequest(task, State::TERMINATED, time);
}