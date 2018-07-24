// Simulator.cpp : Defines the entry point for the console application.
//

#include "SystemModel.h"
#include "Simulator.h"
#include <iostream>

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
	testTask.periodity = PERIODIC;

	//Load demo task into system model
	SystemModel model;
	model.taskList.push_back(&testTask);

	Simulator& sim = Simulator::getInstance();
	sim.systemModel = model;
	sim.scheduler = new BasicScheduler;

	sim.run();

	std::cout << std::endl;
	std::system("pause");
}
