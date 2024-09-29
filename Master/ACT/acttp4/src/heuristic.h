#ifndef HEURISTIC_H
#define HEURISTIC_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "scheduling.h"
#include "task.h"
#include "reader.h"

/**
 * @brief Sort the tasklist by deadline and compare the late of the scheduling
 * 
 * @param tasklist The tasklist to be scheduled
 * @return true 
 * @return false 
 */
bool heuristic_building_with_deadline(TaskList * tasklist);

/**
 * @brief Sort the tasklist by priority and compare the late of the scheduling
 * 
 * @param tasklist The tasklist to be scheduled
 * @return true 
 * @return false 
 */
bool heuristic_building_with_priority(TaskList * tasklist);

/**
 * @brief Sort the tasklist by priority and compare the late of the scheduling
 * 
 * @param tasklist The tasklist to be scheduled
 * @return true 
 * @return false 
 */
bool heuristic_building_with_exec(TaskList * tasklist);

/**
 * @brief Reverse two task between them.
 * 
 * @param task_1 The task one to be reversed
 * @param task_2 The task two to be reversed
 * @return true 
 * @return false 
 */
bool reverse_task(Task * task_1,Task * task_2);

/**
 * @brief Sort tasks by deadline
 * 
 * @param listTask The list to sort
 * @param start The start of the list to sort
 * @param end The end of the list to sort
 * @return true 
 * @return false 
 */
bool merge_separate_sort_by_deadline(Task ** listTask, int start, int end);

/**
 * @brief Sort tasks by priority
 * 
 * @param listTask The list to sort
 * @param start The start of the list to sort
 * @param end The end of the list to sort
 * @return true 
 * @return false 
 */
bool merge_separate_sort_by_priority(Task ** listTask, int start, int end);

/**
 * @brief 
 * 
 */
bool bubble_sort_by_deadline(TaskList *, int size);

/**
 * @brief 
 * 
 */
bool bubble_sort_by_exec(TaskList *, int size);

/**
 * @brief 
 * 
 * @param listTask 
 * @param size 
 * @return true 
 * @return false 
 */
bool bubble_sort_by_priority(TaskList *, int size);

/**
 * @brief 
 * 
 * @param task_1 
 * @param task_2 
 * @return true 
 * @return false 
 */
bool swap_task(Task * task_1,Task * task_2);
#endif