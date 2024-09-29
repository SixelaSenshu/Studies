#ifndef _NEIGHBORHOOD_HEADER_
#define _NEIGHBORHOOD_HEADER_

#include "reader.h"
#include "scheduling.h"
#include "task.h"
#include "heuristic.h"
#include "macro.h"

#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief 
 * 
 */
typedef struct _ListOfTaskList_{
    int capacity;
    int size;
    TaskList ** list;
} ListOfTaskList;

/**
 * @brief Create a List Of Task List object
 * 
 * @param capacity 
 * @return ListOfTaskList* 
 */
ListOfTaskList * createListOfTaskList(int capacity);

/**
 * @brief Destroy a List Of Task List object
 * 
 * @param list 
 */
void destroyListOfTaskList(ListOfTaskList * list);

/**
 * @brief Add a Task List object
 * 
 * @param list 
 * @param tasklist 
 */
void addTaskList(ListOfTaskList * list, TaskList * tasklist);

/**
 * @brief Remove a Task List object
 * 
 * @param list 
 * @param index 
 */
void removeTaskList(ListOfTaskList * list, int index);

/**
 * @brief Print a List Of Task List object
 * 
 * @param list 
 */
void printListOfTaskList(ListOfTaskList * list);

/**
 * @brief simple Local research
 * 
 * @param tasklist the tasklist to optimize
 * @param filename the name of the file to write the result
 * @return true 
 * @return false 
 */
bool VND(TaskList * tasklist,char * filename);

/**
 * @brief 
 * 
 */
typedef struct _Neighborhood_{
    int size;
    int capacity;
    ListOfTaskList ** list;
} Neighborhood;

/** 
 * @brief Create a Neighborhood object
 * 
 * @param capacity
 * @return Neighborhood*
*/
Neighborhood * createNeighborhood(int capacity);

/**
 * @brief Destroy a Neighborhood object
 * 
 * @param neighborhood 
 */
void destroyNeighborhood(Neighborhood * neighborhood);

/**
 * @brief Add a Neighborhood object
 * 
 * @param neighborhood 
 * @param tasklist 
 */
void addNeighborhood(Neighborhood * neighborhood, ListOfTaskList * tasklist);

/**
 * @brief Remove a Neighborhood object
 * 
 * @param neighborhood 
 * @param index 
 */
void removeNeighborhood(Neighborhood * neighborhood, int index);

/**
 * @brief Print a Neighborhood object
 * 
 * @param neighborhood 
 */
void printNeighborhood(Neighborhood * neighborhood);

#endif // !_NEIGHBORHOOD_HEADER_
