// Simulator.cpp : Defines the entry point for the console application.
//


#include "Simulator.h"

int main()
{
	//Create system model
	// Loading from data file?
	// User interface to set it up?

	//Demo Task
	Task testTask;
	testTask.period = 10;
	testTask.deadline = 8;
	testTask.executionTime = 4;

	//Load demo task into system model
	SystemModel model;
	model.taskList.push_back(testTask);

	Simulator& sim = Simulator::getInstance();
	sim.systemModel = model;

	sim.run();
}
