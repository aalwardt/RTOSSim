// Simulator.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "Simulator.h"

int main()
{
	//Create system model
	// Loading from data file?
	// User interface to set it up?

	SystemModel sm; //Predifined and loaded or generated
	Scheduler s;

	Simulator sim(sm, s);

	sim.setup();
	sim.start();
}

