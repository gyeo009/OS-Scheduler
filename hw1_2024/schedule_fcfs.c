/**
 * Implementation of various scheduling algorithms.
 *
 * FCFS scheduling
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "cpu.h"
#include "schedulers.h"
#include "driver.h"

// reference to the head of the list and running_task
struct node *head;
extern Task* running_task;
extern Task* context_switch_task;

/**
 * Run the FCFS scheduler
 */
void schedule()
{
    if (head) {
        // print task list (sanity checker) 
        traverse(head);
        // select next task based on FCFS scheduling policy
        running_task = pickNextTask();
        // add timer interrupt at the expected completion time of the selected task
        // 선택된 Task의 remaining_brust가 timer가 됨
        // 결국 non-preemption scheduling은 timer만 가지고 진행?
        add_timer_interrupt(running_task->remaining_burst);
        // delete the selected task from queue
        delete(&head, running_task);
    }
    else { // there is no task in the queue
        running_task = NULL;
    }
}

/**
 * Return the next task selected to run.
 */
Task *pickNextTask()
{
    return head->task;
}

/** 
 * Add a new task to the list of tasks
 */
void add(int arrival_time, char *name, int burst, int remaining_burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));
    
    newTask->arrival_time = arrival_time;
    strcpy(newTask->name, name);
    newTask->burst = burst;
    newTask->remaining_burst = remaining_burst;

    // insert the new task into the list of tasks 
    insert(&head, newTask);
}

/**
 * Run the dispatcher
 * Note: Do not modify this function
 */
void dispatch()
{
    if (running_task != NULL) {
        if (running_task->remaining_burst > 0) insert(&head, running_task);
        else if (strcmp(running_task->name, "CONTEXT_SWITCH")) {
            complete_task(running_task);
        }
    }
    running_task = context_switch_task;
}

