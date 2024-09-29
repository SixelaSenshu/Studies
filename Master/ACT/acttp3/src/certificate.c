#include "certificate.h"

Binpack *generateCertificate(int nbSac, int nbobjs, int maxWeights, int maxValue)
{

    int i;
    Binpack *certificate = Binpack_create(nbSac, maxWeights, nbobjs);
    if (certificate == NULL)
    {
        goto error;
    }
    for (i = 0; i < nbobjs; i++)
    {
        Backpack_add(certificate->items[rand() % MAX_BACKPACK], rand() % MAX_VALUE);
    }

    return certificate;
error:
    if (certificate != NULL)
        Binpack_free(certificate);
    return NULL;
}

bool verifyCertificate(Binpack *certificate)
{
    int i, j, sum;
    Backpack * bp ;
    // printf("******************************************************************************************************\n");
    for (i = 0; i < certificate->size; i++)
    {
        bp  = certificate->items[i];
        sum = 0;
        for (j = 0; j < bp->size; j++)
        {
            sum += bp->items[j];
        }
        if (sum > bp->weight)
        {
            return false;
        }
    }

    return true;
}
