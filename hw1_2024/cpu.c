/**
 * "Virtual" CPU that runs tasks.
 */

#include <stdio.h>
#include <string.h>

#include "task.h"
#include "cpu.h"
#include "schedulers.h"

extern int timer;
extern Task* running_task;
extern int tick;
extern int logging;

void run_task() {
    running_task->remaining_burst--;
}

void run_context_switch() {
    schedule();
    if (logging && running_task != NULL) printf("[           ] Scheduler selects the next task as [%s]\n\n", running_task->name);
}

// run this task for the specified time slice
void run() {
    if (timer == tick) dispatch();
    tick++;
    if (!strcmp(running_task->name, "CONTEXT_SWITCH")) {
        if (logging) printf("\n[%5d~%5d] CPU is running context switch\n", tick-1, tick);
        run_context_switch();
    }
    else run_task();
}
