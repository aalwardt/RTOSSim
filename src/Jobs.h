//A Job is an event on the TimeAxis
class Job {
	virtual void execute(long time);
	virtual bool isDispatchNecessary(long time);
};

class TaskCreateJob : Job {
	Task& task;
	long time;
};
class TaskTerminateJob : Job {
	Task& task;
	void execute(long time);
	bool isDispatchNecessary();
};