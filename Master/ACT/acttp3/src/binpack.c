#include "binpack.h"

Binpack *Binpack_create(int nbsacs, int maxWeigth, int nbobjs)
{
    int i;
    Binpack *newbackpack = NULL;
    Backpack **items = NULL;
    Backpack *item = NULL;

    if (nbobjs < 0 || maxWeigth < 0 || nbsacs < 0)
    {
        return NULL;
    }

    newbackpack = (Binpack *)malloc(sizeof(Binpack));
    if (newbackpack == NULL)
    {
        fprintf(stderr, "Error to allocate struct * binpack\n");
        return NULL;
    }
    else
    {

        items = (Backpack **)malloc(sizeof(Backpack *) * nbsacs);
        if (items == NULL)
        {
            fprintf(stderr, "Error to allocate backpack ** binpack->items\n");

            goto exit_failure;
        }
        newbackpack->limit = nbsacs;
        newbackpack->size = 0;
        newbackpack->items = items;
        for (i = 0; i < nbsacs; i++)
        {
            //rand() % (maxWeigth *2
            item = Backpack_create(nbobjs,maxWeigth);
            if (item == NULL)
            {
                fprintf(stderr, "Error to allocate backpack * binpack->items[%d]\n", i);

                goto exit_failure;
            }
            Binpack_add(newbackpack,item);
            newbackpack->items[i] = item;
        }
        return newbackpack;
    exit_failure:
        if (newbackpack != NULL)
        {
            {
                if (items != NULL)
                    for (i = 0; i < newbackpack->limit; i++)
                    {
                        if (items[i] != NULL)
                        {
                            free(items[i]);
                        }
                    }
                free(items);
            }
            free(newbackpack);
        }
        return NULL;
    }
}

void Binpack_free(Binpack *binpack)
{
    if (binpack != NULL)
    {
        for (int i = 0; i < binpack->size; i++)
        {
            Backpack_free(binpack->items[i]);
        }
        free(binpack->items);
        free(binpack);
    }
}

int Binpack_add(Binpack *binpack, Backpack *backpack)
{
    if (binpack == NULL)
        return 1;
    if (binpack->limit == binpack->size)
    {
        return 2;
    }
    else
    {
        binpack->items[binpack->size] = backpack;
        binpack->size += 1;
        return 0;
    }
}

void Binpack_toString(Binpack *binpack, int k)
{
    if (binpack != NULL)
    {
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        printf("[BinPack] : Limit : %d, Size : %d\n", binpack->limit, binpack->size);
        if(k == -1){
            for (int i = 0; i < binpack->limit; i++)
            {
                printf("Backpack [%d] -> ", i + 1);
                Backpack_toString(binpack->items[i]);
            }
        }else{
            for (int i = 0; i < k; i++)
            {
                printf("Backpack [%d] -> ", i + 1);
                Backpack_toString(binpack->items[i]);
            }
        }
        printf("\n");
    }
}
