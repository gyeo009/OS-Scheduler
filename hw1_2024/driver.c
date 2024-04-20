/**
 * Driver.c
 *
 * Task is in the format
 *
 *  [arrival time] [name] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
#include "schedulers.h"
#include "cpu.h"
#include "driver.h"

#define SIZE    100

int num_tasks;
int logging = 0; 
int tick = 0; 
int timer = 0;
int waiting_time = 0;
Task* running_task = NULL;
Task* context_switch_task;

int main(int argc, char *argv[])
{
    FILE *in;
    int eof = 0;
    char *temp;
    char task[SIZE];

    int arrival_time = -1;
    char name[5];
    int burst;
    int remaining_burst;

    in = fopen(argv[1],"r");

    if (argc == 3) {
	    if (strcmp(argv[2], "ON") == 0) {
	        logging = 1;
	        printf("LOG ON\n");
	    }
    }

    // init context_switch_task;
    context_switch_task = malloc(sizeof(Task));
    context_switch_task->arrival_time = -1;
    strcpy(context_switch_task->name, "CONTEXT_SWITCH");
    context_switch_task->burst = -1;
    context_switch_task->remaining_burst = -1;
    running_task = context_switch_task;

    while (1) {
        if (running_task == NULL) {
            if (logging) printf("[%11d] there is no ready task in the queue\n", tick);
            break;
        }
        while (arrival_time <= tick) {
            if (!eof && (arrival_time == tick)) { // add the task whose arrival time is equal to the current tick
                if (logging) printf("[%11d] Task [%s] arrives\n", tick, name);
                add(arrival_time, name, burst, remaining_burst);
                num_tasks++;
            }
            if (!eof && (fgets(task, SIZE, in) != NULL)) {
                temp = strtok(task, ",");
                arrival_time = atoi(temp);
                temp = strtok(NULL, ",");
                strcpy(name, temp);
                temp = strtok(NULL, ",");
                burst = atoi(temp);
                temp = strtok(NULL, "\n");
                remaining_burst = burst;
            }
            else if (eof) break;
            else eof = 1;
        }
        run();
    }
    double average_waiting_time = (double)waiting_time / (double)num_tasks;
    printf("\nAverage waiting time is %0.3f\n", average_waiting_time);

    return 0;
}

void complete_task(Task *task) {
    if (logging) printf("[%11d] Task [%s] is finished\n", tick, task->name);
    waiting_time += (tick - task->arrival_time - task->burst);
}

void add_timer_interrupt(int time) {
    timer = tick + time;
    if (logging) printf("[           ] Timer is set at %d\n", timer);
}