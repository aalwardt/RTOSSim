
#include <vector>

struct Task {
	//Deadline Type: HARD or SOFT
	int deadline;
	int priority;
	int offset;
	//Periodity: SPORADIC or PERIODIC
	int period;
	int jitter;
	int contextSwitchingTime;
	int executionTime;
	int responseTime;

	//TODO: Resource usage

	//TODO: Commands for tasks with multiple execution and resource acquisition block
	//For now we will model this with just a single execution time
};

struct Core {
	//TODO: Future use
};

struct SystemModel {
	std::vector<Task> taskList;
};

enum State {
	NON_EXISTING,
	CREATED,
	READY,
	RUNNING,
	BLOCKED,
	TERMINATED
};

