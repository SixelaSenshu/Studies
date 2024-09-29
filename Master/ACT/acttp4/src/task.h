#ifndef _TASK_H_
#define _TASK_H_

/**
 * @file task.h
 * @author 
 * @brief File to define the structure of a task and list of task.
 * @version 0.1
 * @date 2023-11-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <stdint.h>


/**
 * @brief Structure for represent a task.
 * @param time_to_exec Time to execute a task
 * @param available Time to task be available
 * @param deadline Limit of time to complete the task
 * @param priority Order of priority
 * @param overdue Is in late or no
 */
typedef struct _task_{
    /**
     * The time necessary to complete the task
     */
    uint64_t time_to_exec; 

    /**
     * Represent the time to be available 
     */
    uint64_t available; 

    /** Represent the time available after the time_to_exec
     * to complete the task.
    */
    uint64_t deadline;
   
    /**
     * Define the level of priority
     * */
    uint16_t priority; 
    
    /**
     * Define is a task is late or no.
     * */
    bool overdue;     

}Task;

/**
 * @brief Create a Task object
 * 
 * @param time_to_exec Time to execute a task
 * @param available Time to task be available
 * @param deadline Time to complete the task
 * @param priority Priority of the task
 * @return Task* 
 */
Task * createTask(uint64_t time_to_exec, uint64_t available, uint64_t deadline, uint16_t priority);

/**
 * @brief Free a Task object
 * 
 * @param task The task to be free
 */
void freeTask(Task *task);

/**
 * @brief Display a task on the screen
 * 
 * @param task The task to display
 */
void displayTask(Task * task);

/**
 * @brief The structure to represent a list of tasks.
 * @param tasks The ensemble of task
 * @param size The next task
 */
typedef struct _task_list_{

    /**
     * The current task of the list
     */
    Task **tasks;

    /**
     * The number of task in the list
     */
    uint16_t size;

     /**
     * The capacity of task in the list
     */
    uint16_t capacity;

}TaskList;

/**
 * @brief Create a Task List object
 * @param size The size of the list (This one determine the capacity of the list)
 * 
 * @return TaskList* 
 */
TaskList * createTaskList(uint16_t size);

/**
 * @brief Free a TaskList object
 * 
 * @param taskList free a task list
 */
void freeTaskList(TaskList *taskList);

/**
 * @brief Add a task to taskList
 * 
 * @param taskList The list of task
 * @param task The task to add
 */
void addTaskToTaskList(TaskList *taskList, Task *task);

/**
 * @brief Display the taskList on the display
 * 
 * @param taskList display a task list
 */
void displayTaskList(TaskList *taskList);

/**
 * @brief  Shuffle the task list
 * 
 * @param tasklist The task list to shuffle
 */
void shuffleTaskList(TaskList * tasklist);

#endif