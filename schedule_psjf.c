/**
 * Implementation of various scheduling algorithms.
 *
 * Preemptive Shortest Job First scheduling
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

// reference to the head of the list
struct node *head = NULL;
extern Task* running_task;
extern Task* context_switch_task;

/**
 * Run the preemptive shortest job first scheduler
 */
void schedule() 
{
    if (head) {
        // print task list (sanity checker) 
        traverse(head);

        // Implementation SJF - preemption
        running_task = pickNextTask();
        add_timer_interrupt(running_task->remaining_burst);
        delete(&head, running_task);
    }
    else { // there is no task in the queue
        running_task = NULL;
    }
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask()
{
    // Select min value of remaining_burst time of current Queue state
    struct node* cur = head;
    Task* shortest_task = NULL;
    int min_remaining_burst = INT_MAX;

    // Iterate over the tasks in the queue
    while (cur != NULL) {
        // check minimum remaining burst time
        if (cur->task->remaining_burst < min_remaining_burst) {
            min_remaining_burst = cur->task->remaining_burst;
            shortest_task = cur->task;
        }
        // move cur pointer to next element of queue
        cur = cur->next;
    }
    return shortest_task;
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

    // 이때, remaining_burst 가지고 preemption 진행해줘야 함
    // 현재는 context_switch 진행할 때만 schedule을 진행해주는데,
    // add할 때 context_switch를 해줘야 함
    // 현재 Task를 Queue에 저장한 뒤,
    // 현재 Task를 context_switch 상태로 변경 -> 이게 바로 dispatcher가 하는 일
   
    dispatch();
    run();
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

