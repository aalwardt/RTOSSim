// Simulator.cpp : Defines the entry point for the console application.
//

#include "SystemModel.h"
#include "Simulator.h"
#include "EDFScheduler.h"
#include <iostream>

int Task::newID = 1;

int main()
{
	//Create system model
	// Loading from data file?
	// User interface to set it up?

	//Demo Task
	Task task1;
	task1.period = 20;
	task1.deadline = 15;
	task1.executionTime = 8;
	task1.periodity = PERIODIC;

	Task task2;
	task2.period = 8;
	task2.deadline = 6;
	task2.executionTime = 2;
	task2.periodity = PERIODIC;

	Task task3;
	task3.period = 30;
	task3.deadline = 20;
	task3.executionTime = 4;
	task3.periodity = PERIODIC;

	//Load demo task into system model
	SystemModel model(1);
	model.taskList.push_back(&task1);
	model.taskList.push_back(&task2);
	model.taskList.push_back(&task3);

	Simulator& sim = Simulator::getInstance();
	sim.systemModel = model;
	sim.scheduler = new EDFScheduler;

	sim.run();

	std::cout << std::endl;
	std::system("pause");
}
