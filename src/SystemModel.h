
struct SystemModel {

};

enum State {
	NON_EXISTING,
	CREATED,
	READY,
	RUNNING,
	BLOCKED,
	TERMINATED
};

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

	//TODO: Commands for tasks with multiple execution and resource acquisition blocks
};

struct Core {
	//TODO: Future use
};