// Simulator.cpp : Defines the entry point for the console application.
//

#include "SystemModel.h"
#include "Simulator.h"
#include "RMSSCheduler.h"
#include <iostream>

int main()
{
	//Create system model
	// Loading from data file?
	// User interface to set it up?

	//Demo Task
	Task task1;
	task1.period = 10;
	task1.deadline = 10;
	task1.executionTime = 7;
	task1.periodity = PERIODIC;

	Task task2;
	task2.period = 5;
	task2.deadline = 5;
	task2.executionTime = 2;
	task2.periodity = PERIODIC;

	//Load demo task into system model
	SystemModel model;
	model.taskList.push_back(&task1);
	//model.taskList.push_back(&task2);

	Simulator& sim = Simulator::getInstance();
	sim.systemModel = model;
	sim.scheduler = new RMSScheduler;

	sim.run();

	std::cout << std::endl;
	std::system("pause");
}
