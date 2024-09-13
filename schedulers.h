#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

// add a task to the list 
void add(int arrival_time, char *name, int burst, int remaining_burst);

// invoke the scheduler
void schedule();

// pick next task (inside scheduler)
Task *pickNextTask();

// invoke the dispather 
void dispatch();
