
#include "../../headers/triplets/MainTriplet.h"

int main(int argc, char *argv[])
{
    Triplet *triplet1 = NULL, *triplet2 = NULL;
    double scalar;
    bool res = false;
    bool ok = false;
    double resDouble;
    char *method = NULL, *token = NULL, *token2 = NULL;
    char type, type2;
    double x, y, z, x2, y2, z2;

    if (argv[1] == NULL)
    {
        fprintf(stdout, "Interdit");
        goto quit;
    }

    //___________________________ Lecture du premier triplet
    token = strtok(argv[1], ",");
    method = strtok(NULL, ",");
    token2 = strtok(NULL, ",");
    if (token == NULL || method == NULL)
        goto quit;

    char *subtoken = strtok(token, " ");
    if (subtoken == NULL)
        goto quit;
    type = subtoken[0];

    subtoken = strtok(NULL, " ");
    if (subtoken == NULL)
        goto quit;
    x = (double)atof(subtoken);

    subtoken = strtok(NULL, " ");
    if (subtoken == NULL)
        goto quit;
    y = (double)atof(subtoken);

    subtoken = strtok(NULL, " ");
    if (subtoken == NULL)
        goto quit;
    z = (double)atof(subtoken);

    if (type == 'P')
    {
        triplet1 = triplet_create_point(x, y, z);
    }
    else if (type == 'C')
    {
        triplet1 = triplet_create_color(x, y, z);
    }
    else if (type == 'V')
    {
        triplet1 = triplet_create_vector(x, y, z);
    }
    else
    {
        goto quit;
        fprintf(stdout, "Interdit");
    }
    if (!triplet1)
        goto quit;
    //___________________________ Lecture de la method
    token = strtok(method, "");
    if (token == NULL)
        goto quit;
    //___________________________ Lecture du deuxieme triplet/scalaire
    token = strtok(token2, "");
    if (token2 != NULL)
    {

        if (token[0] >= '0' && token[0] <= '9')
        {
            scalar = atof(token);
            if (!strcmp(method, "mul"))
            {
                res = triplet_mul(triplet1, scalar);
            }
        }
        else if (token[0] != '\0' || token[0] != '\n')
        {
            subtoken = strtok(token, " ");
            if (subtoken == NULL)
                goto quit;
            type2 = subtoken[0];

            subtoken = strtok(NULL, " ");
            if (subtoken == NULL)
                goto quit;
            x2 = (double)atof(subtoken);

            subtoken = strtok(NULL, " ");
            if (subtoken == NULL)
                goto quit;
            y2 = (double)atof(subtoken);

            subtoken = strtok(NULL, " ");
            if (subtoken == NULL)
                goto quit;
            z2 = (double)atof(subtoken);
            if (type2 == 'P')
            {
                triplet2 = triplet_create_point(x2, y2, z2);
            }
            else if (type2 == 'C')
            {
                triplet2 = triplet_create_color(x2, y2, z2);
            }
            else if (type2 == 'V')
            {
                triplet2 = triplet_create_vector(x2, y2, z2);
            }
            else
            {
                fprintf(stdout, "Interdit");
                goto quit;
            }

            if (!triplet2)
                goto quit;
            if (!strcmp(method, "add"))
            {
                res = triplet_add(triplet1, triplet2);
            }
            else if (!strcmp(method, "sub"))
            {
                res = triplet_sub(triplet1, triplet2);
            }
            else if (!strcmp(method, "dot"))
            {
                resDouble = triplet_scalar_product(triplet1, triplet2);
                if (resDouble != false)
                {
                    fprintf(stdout, "%.1f", resDouble);
                    ok = true;
                }
            }
            else if (!strcmp(method, "cross"))
            {
                res = triplet_vectorial_product(triplet1, triplet2);
            }
            else if (!strcmp(method, "times"))
            {
                res = triplet_schur(triplet1, triplet2);
            }
        }
    }
    else
    {
        if (!strcmp(method, "len"))
        {
            resDouble = triplet_length(triplet1);
            fprintf(stdout, "%.1f", resDouble);
            ok = true;
        }
        else if (!strcmp(method, "hat"))
        {
            res = triplet_normalization(triplet1);
        }
        else
        {
            fprintf(stdout, "Interdit");
            goto quit;
        }
    }

    token = strtok(NULL, ",");

    //___________________________ Lecture de la methode & application

    if (res)
    {
        triplet_display((Triplet){triplet1->type, triplet1->x, triplet1->y, triplet1->z});
    }
    else if (!ok)
    {
        fprintf(stdout, "Interdit");
    }

    //___________________________ Désallocation

    if (triplet1 != NULL)
        triplet_destroy(triplet1);
    if (triplet2 != NULL)
        triplet_destroy(triplet2);
    return EXIT_SUCCESS;
quit:
    if (triplet1 != NULL)
        triplet_destroy(triplet1);
    if (triplet2 != NULL)
        triplet_destroy(triplet2);
    return EXIT_FAILURE;
}
