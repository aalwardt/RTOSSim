#include "Jobs.h"

void TaskTerminateJob::execute(long time) {
	Simulator::getInstance().scheduler.stateChangeRequest(task, State::TERMINATED, time);
}
bool TaskTerminateJob::isDispatchNecessary() {
	return true;
}