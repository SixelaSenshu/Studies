#ifndef _PARTITION_H_
#define _PARTITION_H_

// #include <macro.h>
#include "./binpack.h"

/**
 * @brief 
 * 
 */
typedef struct partition
{
    int * p1;
    int * p2;
    int nbItems1;
    int nbItems2;
    int limit;
}Partition;

/**
 * @brief 
 * 
 */
typedef struct Sum
{
    int sum;
    int *sp;
    int nbItems;
    int limit;
}Sum;

/**
 * @brief 
 * 
 * @param binpack 
 * @return Partition* 
 */
Partition * Partition_create();


/**
 * @brief 
 * 
 * @param partition 
 * @return Binpack* 
 */
Binpack * Binpack_create_with_partition(Partition * partition);

/**
 * @brief 
 * 
 * @param items1 
 * @param size1 
 * @param items2 
 * @param size2 
 * @param partition 
 */
void addItemsPartition(int items1[], int size1, int items2[], int size2, Partition * partition);


/**
 * @brief 
 * 
 * @return Sum* 
 */
Sum * Sum_create();

/**
 * @brief 
 * 
 * @param items 
 * @param size 
 * @param p 
 * @param sum 
 */
void addItemsSum(int items[], int size, int p, Sum * sum);

/**
 * @brief 
 * 
 * @param sum 
 * @return Partition* 
 */
Partition * Partition_create_with_sum(Sum * sum);

/**
 * @brief 
 * 
 */
void Display_Sum(Sum * sum);

#endif // !H_

