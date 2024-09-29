#include "../../headers/triplets/Triplet.h"

extern Triplet *triplet_create_point(double x, double y, double z)
{
    Triplet *triplet = triplet_create(x, y, z);
    if (!triplet)
    {
        return NULL;
    }
    else
    {
        triplet->type = POINT;
        triplet->sub = true;
        triplet->mul = true;
    }
    return triplet;
}

extern Triplet *triplet_create_vector(double x, double y, double z)
{
    Triplet *triplet = triplet_create(x, y, z);
    if (!triplet)
    {
        return NULL;
    }
    else
    {
        triplet->type = VECTOR;
        triplet->add = true;
        triplet->sub = true;
        triplet->mul = true;
        triplet->scalProd = true;
        triplet->vectProd = true;
        triplet->length = true;
        triplet->normalization = true;
    }
    return triplet;
}

extern Triplet *triplet_create_color(double x, double y, double z)
{
    Triplet *triplet = triplet_create(x, y, z);
    if (!triplet)
    {
        return NULL;
    }
    else
    {
        triplet->type = COLOR;
        triplet->add = true;
        triplet->mul = true;
        triplet->schurProd = true;
    }
    return triplet;
}

extern Triplet *triplet_create(double x, double y, double z)
{
    Triplet *newTriplet = (Triplet *)malloc(sizeof(Triplet));
    if (!newTriplet)
    {
        fprintf(stderr, "[ALLOCATION] Problème d'allocation\n");
        return NULL;
    }
    newTriplet->type = NONE;
    newTriplet->add = false;
    newTriplet->sub = false;
    newTriplet->mul = false;
    newTriplet->scalProd = false;
    newTriplet->vectProd = false;
    newTriplet->schurProd = false;
    newTriplet->length = false;
    newTriplet->normalization = false;
    newTriplet->x = x;
    newTriplet->y = y;
    newTriplet->z = z;
    return newTriplet;
}

extern Triplet triplet_point(double x, double y, double z)
{
    return (Triplet){POINT, x, y, z, false, true, true, false, false, false, false, false};
}

extern Triplet triplet_vector(double x, double y, double z)
{
    return (Triplet){VECTOR, x, y, z, true, true, true, true, true, false, true, true};
}

extern Triplet triplet_color(double x, double y, double z)
{
    return (Triplet){COLOR, x, y, z, true, false, true, false, false, true, false, false};
}

extern bool triplet_add(Triplet *current, Triplet *added)
{
    if (current && added)
    {

        if (current->type == VECTOR && added->type == POINT)
        {
            current->x = +added->x;
            current->y = +added->y;
            current->z = +added->z;
            goto switchP;
        }
        else if (current->type == POINT && added->type == VECTOR)
        {
            added->type = POINT;
            added->sub = true;
            added->mul = true;
            added->add = false;
            added->scalProd = false;
            added->vectProd = false;
            added->length = false;
            added->normalization = false;
            current->x += added->x;
            current->y += added->y;
            current->z += added->z;
        }
        else if (current->add && added->add)
        {
            current->x += added->x;
            current->y += added->y;
            current->z += added->z;
        }
        else
        {
            return false;
        }
        return true;
    }

    return false;
switchP:
    current->type = POINT;
    current->sub = true;
    current->mul = true;
    current->add = false;
    current->scalProd = false;
    current->vectProd = false;
    current->schurProd = false;
    current->length = false;
    current->normalization = false;

    return true;
}

extern bool triplet_sub(Triplet *current, Triplet *subtracted)
{
    if (current && subtracted)
    {
        if (current->sub && subtracted->sub)
        {
            if (current->type == POINT && subtracted->type == POINT)
            {
                current->type = VECTOR;
                current->add = true;
                current->sub = true;
                current->mul = true;
                current->scalProd = true;
                current->vectProd = true;
                current->length = true;
                current->normalization = true;
            }
            current->x -= subtracted->x;
            current->y -= subtracted->y;
            current->z -= subtracted->z;
            return true;
        }
    }
    return false;
}

extern bool triplet_mul(Triplet *current, double scalar)
{
    if (!current || !current->mul)
        return false;
    else
    {
        current->x = current->x * scalar;
        current->y = current->y * scalar;
        current->z = current->z * scalar;
        return true;
    }
}

extern double triplet_scalar_product(Triplet *current, Triplet *multiplied)
{
    if (!current || !multiplied || !multiplied->scalProd || !current->scalProd)
        return false;
    else
        return (current->x * multiplied->x) + (current->y * multiplied->y) + (current->z * multiplied->z);
}

extern bool triplet_vectorial_product(Triplet *current, Triplet *multiplied)
{
    if (!current || !multiplied || !multiplied->vectProd || !current->vectProd)
        return false;
    else
    {
        double newX, newY, newZ;
        newX = (current->y * multiplied->z) - (current->z * multiplied->y);
        newY = (current->z * multiplied->x) - (current->x * multiplied->z);
        newZ = (current->x * multiplied->y) - (current->y * multiplied->x);
        current->x = newX;
        current->y = newY;
        current->z = newZ;
        return true;
    }
}

extern bool triplet_schur(Triplet *current, Triplet *mulitplied)
{
    if (current && mulitplied && current->schurProd && mulitplied->schurProd)
    {
        current->x = current->x * (double)mulitplied->x;
        current->y = current->y * (double)mulitplied->y;
        current->z = current->z * (double)mulitplied->z;
        return true;
    }

    return false;
}

extern double triplet_length(Triplet *current)
{
    if (!current || !current->length)
        return false;
    else
        return sqrt((current->x * current->x) + (current->y * current->y) + (current->z * current->z));
}

extern bool triplet_normalization(Triplet *current)
{
    if (!current || !current->normalization)
    {
        return false;
    }
    else
    {
        double den = (double)1 / (double)triplet_length(current);
        triplet_mul(current, den);
        return true;
    }
}

extern void triplet_destroy(Triplet *triplet)
{
    if (triplet)
    {
        free(triplet);
    }
}

extern void triplet_display(Triplet triplet)
{
    if (triplet.type == POINT)
    {
        fprintf(stdout, "P ");
    }
    else if (triplet.type == VECTOR)
    {
        fprintf(stdout, "V ");
    }
    else if (triplet.type == COLOR)
    {
        fprintf(stdout, "C ");
    }
    if (fmod(triplet.x, 1))
    {
        fprintf(stdout, "%.9g ", triplet.x);
    }
    else
    {
        fprintf(stdout, "%.1f ", triplet.x);
    }
    if (fmod(triplet.y, 1))
    {
        fprintf(stdout, "%.9g ", triplet.y);
    }
    else
    {
        fprintf(stdout, "%.1f ", triplet.y);
    }
    if (fmod(triplet.z, 1))
    {
        fprintf(stdout, "%.9g\n", triplet.z);
    }
    else
    {
        fprintf(stdout, "%.1f\n", triplet.z);
    }
}
