#include "backpack.h"

Backpack *Backpack_create(int limit, int weight)
{
    if (limit < 0 || weight < 0)
    {
        return NULL;
    }
    Backpack *newbackpack = NULL;
    newbackpack = (Backpack *)malloc(sizeof(Backpack));
    if (newbackpack == NULL)
    {
        fprintf(stderr, "Error to allocate struct * backpack\n");
        return NULL;
    }
    else
    {
        int *items = NULL;

        items = (int *)malloc(sizeof(int) * limit);
        if (items == NULL)
        {
            fprintf(stderr, "Error to allocate int * backpack->items\n");
            free(newbackpack);
            return NULL;
        }
        newbackpack->size = 0;
        newbackpack->limit = limit;
        newbackpack->items = items;
        newbackpack->weight = weight;
        return newbackpack;
    }
}

void Backpack_free(Backpack *backpack)
{
    if (backpack != NULL)
    {
        free(backpack->items);
        free(backpack);
    }
}

int Backpack_add(Backpack *backpack, int item)
{
    if (backpack == NULL)
    {
        fprintf(stderr, "Backpack is empty\n");
        return 1;
    }
    if (backpack->limit == backpack->size)
    {
        fprintf(stderr, "Backpack size == limit\n");
        return 2;
    }
    else
    {
        backpack->items[backpack->size] = item;
        backpack->size+=1;
        return 0;
    }
}

void Backpack_toString(Backpack *backpack)
{
    if (backpack != NULL)
    {
        printf("Limit : %d, Size : %d, Weight : %d \n", backpack->limit, backpack->size, backpack->weight);
        for (int i = 0; i < backpack->size; i++)
        {
            printf("{%d}", backpack->items[i]);
        }
        printf("\n");
    }
}

