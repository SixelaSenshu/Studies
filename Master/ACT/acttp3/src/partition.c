#include "partition.h"

Partition * Partition_create(){
    Partition * newpartition = NULL;
    int * p1 = NULL;
    int * p2 = NULL;
    int limit = 0;
    newpartition = (Partition *)malloc(sizeof(Partition));
    if (newpartition == NULL)
    {
        fprintf(stderr, "Error to allocate struct * partition\n");
        return NULL;
    }
    else
    {
        p1 = (int *)malloc(sizeof(int) * limit);
        if (p1 == NULL)
        {
            fprintf(stderr, "Error to allocate int * partition->p1\n");
            goto exit_failure;
        }
        p2 = (int *)malloc(sizeof(int) * limit);
        if (p2 == NULL)
        {
            fprintf(stderr, "Error to allocate int * partition->p2\n");
            goto exit_failure;
        }
        newpartition->p1 = p1;
        newpartition->p2 = p2;
        newpartition->limit = limit;
        newpartition->nbItems1 = 0;
        newpartition->nbItems2 = 0;
        return newpartition;
    exit_failure:
        if (newpartition != NULL)
        {
            if (p1 != NULL)
            {
                free(p1);
            }
            if (p2 != NULL)
            {
                free(p2);
            }
            free(newpartition);
        }
        return NULL;
    }
}

void addItemsPartition(int items1[], int size1, int items2[], int size2, Partition * partition){
    for(int i = 0; i < size1; i++){
        partition->p1[partition->nbItems1] = items1[i];
        partition->nbItems1 += 1;
    }
    for(int i = 0; i < size2; i++){
        partition->p2[partition->nbItems2] = items2[i];
        partition->nbItems2 += 1;
    }
}


Binpack * Binpack_create_with_partition(Partition * partition){ 
        Binpack * newbinpack = NULL;
        int capacity = 0;
        capacity = partition->limit * 2;
        newbinpack = Binpack_create(5,partition->limit,2);
        for(int i = 0; i < partition->nbItems1; i++ ){
            newbinpack->items[0]->items[i] = partition->p1[i];
            newbinpack->items[0]->size += 1;
        }
        for(int i = 0; i < partition->nbItems2; i++ ){
            newbinpack->items[1]->items[i] = partition->p2[i];
            newbinpack->items[1]->size += 1;
        }
        newbinpack->items[0]->weight = 30;
        newbinpack->items[1]->weight = 30;
        return newbinpack;
}

Sum * Sum_create(){
    Sum * newsum = NULL;
    int sum = 0;
    int *sp = NULL;
    int limit = 0;
    newsum = (Sum *)malloc(sizeof(Sum));
    if (newsum == NULL)
    {
        fprintf(stderr, "Error to allocate struct * sum\n");
        return NULL;
    }
    else
    {
        sp = (int *)malloc(sizeof(int) * limit);
        if (sp == NULL)
        {
            fprintf(stderr, "Error to allocate int * sum->sp\n");
            goto exit_failure;
        }
        newsum->sum = 0;
        newsum->nbItems = 0;
        newsum->sp = sp;
        newsum->limit = limit;
        return newsum;
    exit_failure:
        if (newsum != NULL)
        {
            if (sp != NULL)
            {
                free(sp);
            }
            free(newsum);
        }
        return NULL;
    }
}

void addItemsSum(int items[], int size, int p, Sum * sum){
    sum->sum = p;
    for(int i = 0; i < size; i++){
        sum->sp[sum->nbItems] = items[i];
        sum->nbItems += 1;
    }
}

Partition * Partition_create_with_sum(Sum * sum){
    Partition * newpartition = NULL;
    newpartition = Partition_create();
    newpartition->nbItems1 = sum->nbItems;
    newpartition->nbItems2 = 1;
    newpartition->limit = sum->limit;
    newpartition->p1 = sum->sp;
    newpartition->p2 = sum->sum;
}  

void Display_Sum(Sum * sum){
    printf("Sum : %d\n",sum->sum);
    printf("Items : ");
    for(int i = 0; i < sum->nbItems; i++){
        printf("%d ",sum->sp[i]);
    }
    printf("\n");
}