#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_

/**
 * @file scheduling.h
 * @author
 * @brief The file to define the structure of a scheduling.
 * @version 0.1
 * @date 2023-11-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "reader.h"
#include "task.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <stdint.h>

/**
 * @brief The structure to represent a scheduling.
 * @param task The current task
 * @param late The time where the task must already be completed
 * @param next The next task of sheduling
 */
typedef struct _scheduling_ {
    /**
     * The current task
     */
    Task *task;

    /**
     * The time where the task must already be completed
     */
    uint64_t late;    

    /**
     * The time where the scheduling has started
     */
    uint64_t time_to_start;

    /**
     * The next task of sheduling
     */
    struct _scheduling_ *next;
} Scheduling;


/**
 * @brief Create a Scheduling object
 * 
 * @param task The task to init scheduling
 * @return Scheduling* 
 */
Scheduling * createScheduling(Task *task);

/**
 * @brief Free a Scheduling object
 * 
 * @param scheduling The scheduling to free
 */
void freeScheduling(Scheduling *scheduling);

/**
 * @brief Display a Scheduling object on the console
 * 
 * @param scheduling The scheduling to display
 */
void displayScheduling(Scheduling *scheduling);

/**
 * @brief Get the Delay object
 * 
 * @param scheduling The scheduling to get delay
 * @return uint64_t The delay
 */
uint64_t getDelay(Scheduling *scheduling);

/**
 * @brief Add a task to sheduling
 * 
 * @param scheduling The scheduling to add task
 * @param task The task to add
 * @return int The code error
 */
int addTaskToScheduling(Scheduling *scheduling, Task *task);

/**
 * @brief Add a tasklist to sheduling
 * 
 * @param tasklist The tasklist to add
 * @return Scheduling* 
 */
Scheduling * addTaskListToScheduling(TaskList *tasklist);

/**
 * @brief Compare the task list with a random shuffle
 * 
 * @param tasklist the tasklist to shuffe
 */
bool compareRandomShuffle(char * fname);

#endif // !__SCHEDULING_H_
