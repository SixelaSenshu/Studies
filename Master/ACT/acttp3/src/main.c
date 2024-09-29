#include "certificate.h"
#include "partition.h"

static int test_core_dumped_backpack(void);
static int test_core_dumped_binpack(void);
static int test_core_dumped_certificate(int rand);

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char *argv[])
{
    int err;
    if(test_core_dumped_binpack())
        return EXIT_FAILURE;
    if(test_core_dumped_backpack())
        return EXIT_FAILURE;
    for(int i = 0; i < 20; i++){
        err = test_core_dumped_certificate(i);
        if(err == -1){
            return EXIT_FAILURE;
        }
    }
    // Reduction binpack to partition
    Partition * partition = Partition_create();
    int tab1[5] = {6,7,2,5,10};
    int tab2[2] =  {20,10};
    addItemsPartition(tab1, 5, tab2, 2,partition);
    Binpack * binpackWithPartition = Binpack_create_with_partition(partition);
    Binpack_toString(binpackWithPartition,2);
    // Reduction Sum to partition
    Sum * sum = Sum_create();
    int tab3[5] = {6,7,2,5,10};
    int sumnb = 30;
    addItemsSum(tab3,5,sumnb,sum);
    Partition * partitionWithSum = Partition_create_with_sum(sum);
    Display_Sum(sum);
    // Binpack * binpackWithCombinaison = Binpack_create_with_partition(partitionWithSum);
    // Binpack_toString(binpackWithCombinaison,2);
    return EXIT_SUCCESS;
}

/**
 * @brief 
 * 
 * @param rand
 * @return int 
 */
static int test_core_dumped_certificate(int rand){

    srand(rand);
    Binpack *certificate = generateCertificate(MAX_BACKPACK, MAX_ITEMS, MAX_WEIGHT, MAX_VALUE);
    if (certificate == NULL)
    {
        return -1;
    };
    if (verifyCertificate(certificate))
    {
        printf("The certificate is good [%d]\n",rand);
        Binpack_toString(certificate,-1);
        Binpack_free(certificate);
        return 1;
    }
    else
    {
        Binpack_free(certificate);
        return 0;
    }
}

/**
 * @brief
 *
 * @return true
 * @return false
 */
static int test_core_dumped_backpack(void)
{
    int i;
    Backpack *bp = Backpack_create(MAX_ITEMS, MAX_WEIGHT);

    if (bp == NULL)
    {
        printf("Error to allocate bp (BACKPACK)");
        return EXIT_FAILURE;
    }
    for (i = 0; i < bp->limit; i++)
    {
        Backpack_add(bp, rand() % MAX_VALUE);
    }
    Backpack_free(bp);
    return EXIT_SUCCESS;
}

/**
 * @brief 
 * 
 * @return int 
 */
static int test_core_dumped_binpack(void)
{
    int i, j;
    Binpack *bp = Binpack_create(MAX_ITEMS, MAX_WEIGHT, MAX_BACKPACK);
    Backpack *backp;
    if (bp == NULL)
    {
        printf("Error to allocate bp (BINPACK)");
        return EXIT_FAILURE;
    }
    for (i = 0; i < bp->limit; i++)
    {
        backp = bp->items[i];
        for (j = 0; j < backp->limit; j++)
        {
            Backpack_add(backp, rand() % MAX_VALUE);
        }
    }
    Binpack_free(bp);
    return EXIT_SUCCESS;
}



