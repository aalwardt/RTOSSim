// Simulator.cpp : Defines the entry point for the console application.
//


#include "Simulator.h"

int main()
{
	//Create system model
	// Loading from data file?
	// User interface to set it up?

	Simulator& sim = Simulator::getInstance();

	sim.setup();
	//sim.start();
}

