#ifndef _BACKPACK_H_
#define _BACKPACK_H_

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "macro.h"

/**
 * @brief
 *
 */
typedef struct _Backpack_
{
    int size;
    int limit;
    int weight;
    int *items;

} Backpack;

/**
 * @brief
 *
 * @param limit
 * @param weigth
 * @return Backpack*
 */
Backpack *Backpack_create(int limit, int weight);

/**
 * @brief
 *
 * @param backpack
 */
void Backpack_free(Backpack *backpack);

/**
 * @brief
 *
 * @param backpack
 * @param item
 * @return int
 */
int Backpack_add(Backpack *backpack, int item);

/**
 * @brief
 *
 * @param backpack
 */
void Backpack_toString(Backpack *backpack);

#endif //!_BACKPACK_H_