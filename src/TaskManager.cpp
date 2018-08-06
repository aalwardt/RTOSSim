#include "TaskManager.h"
#include "AxisEvent.h"
#include "Simulator.h"
#include <iostream>

void TaskMonitor::create(Task* t, long time) {
	//Only create a task if it doesn't already exist
	if (state == NON_EXISTING) {
		//Set the absolute deadline of the task
		absoluteDeadline = time + t->deadline;
		//Reset the elapsed execution time
		elapsedExecutionTime = 0;
		state = State::CREATED;
		std::cout << time << '\t' << t->getID() << "\tTask created\n";
		//If task is periodic, add new task creation event for next release
		//Note: This task should not be removed from the TimeAxis, so we don't need to store this pointer
		if (t->periodity == PERIODIC) {
			AxisEvent * newTaskJob = new TaskCreateEvent(t);
			Simulator::getInstance().timeAxis.addJob(newTaskJob, time + t->period);
		}
	}
	else {
		//TODO: Throw exception?
		std::cerr << time << '\t' << t->getID() << "\tILLEGAL STATE CHANGE TO CREATED. MISSED DEADLINE?\n";
	}
}

void TaskMonitor::makeReady(Task* t, long time) {
	//Only make ready if the task is RUNNING or CREATED
	switch (state) {
	case RUNNING:
		//If already running, update the elapsed execution time
		elapsedExecutionTime += time - executionStartTime;

		//Remove the job generated for the end of this execution block
		Simulator::getInstance().timeAxis.removeJob(nextJob, executionEndTime);
		std::cout << time << '\t' << t->getID() << "\tTask preempted\n";
	case CREATED:
		state = READY;
		std::cout << time << '\t' << t->getID() << "\tTask ready\n";
		break;
	default:
		//TODO: Throw exception?
		std::cerr << time << '\t' << t->getID() << "\tILLEGAL STATE CHANGE TO READY\n";
		break;
	}
}

void TaskMonitor::run(Task* t, long time) {
	//Only run a task if it's ready
	if (state == READY) {
		executionStartTime = time; //Set the execution time to start here
		executionEndTime = time + t->executionTime - elapsedExecutionTime;
		state = State::RUNNING;

		//Add TaskTerminateJob at end of execution 
		nextJob = new TaskTerminateEvent(t);
		Simulator::getInstance().timeAxis.addJob(nextJob, executionEndTime);

		std::cout << time << '\t' << t->getID() << "\tTask running\n";
	}
	else {
		std::cerr << time << '\t' << t->getID() << "\tILLEGAL STATE CHANGE TO RUNNING\n";
		//TODO: Throw exception?
	}
}

void TaskMonitor::terminate(Task* t, long time) {
	//Only terminate a task that is running (it's execution has finished)
	if (state == RUNNING) {
		state = State::TERMINATED;
		std::cout << time << '\t' << t->getID() << "\tTask terminated\n";
	}
	else {
		std::cerr << time << '\t' << t->getID() << "\tILLEGAL STATE CHANGE TO TERMINATED\n";
		//TODO: Throw exception?
	}
}

void TaskMonitor::remove(Task* t, long time) {
	//Only remove tasks that have been terminated
	if (state == TERMINATED) {
		state = State::NON_EXISTING;
		std::cout << time << '\t' << t->getID() << "\tTask removed\n";
	}
	else {
		std::cerr << time << '\t' << t->getID() << "\tILLEGAL STATE CHANGE TO REMOVE\n";
		//TODO: Throw exception?
	}
}