/**
 * Implementation of various scheduling algorithms.
 *
 * Round-Robin scheduling
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

#define QUANTUM 1000

// reference to the head of the list
struct node *head = NULL;
extern Task* running_task;
extern Task* context_switch_task;

/**
 * Run the round robin scheduler
 */
void schedule() 
{
    if (head) {
        // print task list (sanity checker) 
        traverse(head);
        
        // 현재 Task 불러오기
        running_task = pickNextTask();
        
        // timer 를 min(time quantum, running_task->remaining_burst) 로 설정
        add_timer_interrupt(min(QUANTUM, running_task->remaining_burst));

        // time == timer일 때 scheduling보다 항상 dispatch가 먼저 실행되기 때문에
        // 지금 Task가 다시 큐의 맨 뒤로 삽입된 후
        // 아래 delete 연산을 사용해 현재 가리키고 있는 Task를 큐에서 삭제
        // 결과적으로 큐의 맨 앞에있어서 현재 작업중이었던 Task가 작업 이후 큐의 맨 뒤로 삽입됨
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

