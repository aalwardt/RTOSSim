//A Job is an event on the TimeAxis
class Job {
public:
	virtual void execute(long time);
	virtual bool isDispatchNecessary();
};

class TaskCreateJob : Job {
	Task& task;
public:
	TaskCreateJob(Task& task) : task(task) {}
	void execute(long time);
	bool isDispatchNecessary() { return true; }
};

class TaskTerminateJob : Job {
	Task& task;
public:
	TaskTerminateJob(Task& task) : task(task) {}
	void execute(long time);
	bool isDispatchNecessary() { return true; }
};