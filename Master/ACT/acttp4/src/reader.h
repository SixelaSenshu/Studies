#ifndef _READER_H_
#define _READER_H_

/**
 * @file reader.h
 * @author
 * @brief The file to represent a reader of file
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
#include "scheduling.h"
#include "task.h"

/**
 * @brief Function to read a file and generate a lisk of task
 * 
 * @param filename The name of file 
 * @return TaskList* 
 */
TaskList *readFile(char *filename);

#endif // !_READER_H_