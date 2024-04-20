/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"
#include "cpu.h"

extern int time;
extern int tick;
extern int logging;

// add a new task to the list of tasks
void insert(struct node **head, Task *newTask) {
	struct node *newNode = malloc(sizeof(struct node));
	newNode->task = newTask;
	newNode->next = NULL;

	struct node *tail;

	tail = *head;

	if(tail == NULL) {
		*head = newNode;
	}
	else {
		while(tail->next != NULL) {
			tail = tail->next;
		}
		tail->next = newNode;
	}
}

// delete the selected task from the list
void delete(struct node **head, Task *task) {
    struct node *temp;
    struct node *prev;

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(struct node *head) {
    struct node *temp;
    temp = head;

    if (logging) {
        printf("[%11d] Task list in the queue\n", tick);
        printf("                  arr_time task     burst    burst_remain\n");
        while (temp != NULL) {
            printf("                  [%6d] [%6s] [%6d] [%6d]\n",temp->task->arrival_time, temp->task->name, temp->task->burst, temp->task->remaining_burst);
            temp = temp->next;
        }
    }
}
