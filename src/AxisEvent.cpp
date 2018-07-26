#include "AxisEvent.h"
#include "Simulator.h"
#include "Scheduler.h"

void TaskCreateEvent::execute(long time) {
	Simulator::getInstance().scheduler->stateChangeRequest(task, State::CREATED, time);
}

void TaskTerminateEvent::execute(long time) {
	Simulator::getInstance().scheduler->stateChangeRequest(task, State::TERMINATED, time);
}