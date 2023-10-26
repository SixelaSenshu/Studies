#include "../../headers/Tools/Triangle.h"

extern double intersection_plane(Triplet lookFrom, Triplet direction, Triplet pointplane, Triplet vectorplane)
{
    double resDifference, resNormal;
    Triplet difference = triplet_vector(pointplane.x, pointplane.y, pointplane.z);
    triplet_sub(&difference, &lookFrom);
    resDifference = triplet_scalar_product(&difference, &vectorplane);
    resNormal = triplet_scalar_product(&direction, &vectorplane);
    // printf("_%f_", resNormal / resDifference);
    if (resNormal == 0)
    {
        return -1;
    }
    return resDifference / resNormal;
}

// si point dans triangle alors ok

extern Triplet get_point_in_plane(Triplet lookFrom, Triplet direction, Plane plane)
{
    Triplet res = triplet_vector(lookFrom.x, lookFrom.y, lookFrom.z);
    Triplet distance_int = triplet_vector(direction.x, direction.y, direction.z);
    double intersection = intersection_plane(res, distance_int, plane.point, plane.vector);
    triplet_mul(&distance_int, intersection);
    triplet_add(&res, &distance_int);
    return res;
}

extern Triplet normal_of_triangle(Triplet a, Triplet b, Triplet c)
{
    Triplet diff_ba, diff_ca;
    diff_ba = triplet_point(b.x, b.y, b.z);
    diff_ca = triplet_point(c.x, c.y, c.z);
    triplet_sub(&diff_ba, &a);
    triplet_sub(&diff_ca, &a);
    triplet_vectorial_product(&diff_ba, &diff_ca);
    triplet_normalization(&diff_ba);
    return diff_ba;
}

extern bool point_in_triangle(Triplet a, Triplet b, Triplet c, Triplet point)
{
    Triplet normal = normal_of_triangle(a, b, c);
    Triplet diff_ba, diff_cb, diff_ac, diff_pa, diff_pb, diff_pc;
    double na, nb, nc;
    diff_ba = triplet_point(b.x, b.y, b.z);
    triplet_sub(&diff_ba, &a);
    diff_pa = triplet_point(point.x, point.y, point.z);
    triplet_sub(&diff_pa, &a);
    triplet_vectorial_product(&diff_ba, &diff_pa);
    nb = triplet_scalar_product(&diff_ba, &normal);
    if (nb < 0)
        return false;
    diff_cb = triplet_point(c.x, c.y, c.z);
    triplet_sub(&diff_cb, &b);
    diff_pb = triplet_point(point.x, point.y, point.z);
    triplet_sub(&diff_pb, &b);
    triplet_vectorial_product(&diff_cb, &diff_pb);
    nc = triplet_scalar_product(&diff_cb, &normal);
    if (nc < 0)
        return false;
    diff_ac = triplet_point(a.x, a.y, a.z);
    triplet_sub(&diff_ac, &c);
    diff_pc = triplet_point(point.x, point.y, point.z);
    triplet_sub(&diff_pc, &c);
    triplet_vectorial_product(&diff_ac, &diff_pc);
    na = triplet_scalar_product(&diff_ac, &normal);
    if (na < 0)
        return false;
    return true;
}

extern Triplet get_gravity_point_triangle(Triplet p1, Triplet p2, Triplet p3)
{
    double x = (p1.x + p2.x + p3.x) / 3, y = (p1.y + p2.y + p3.y) / 3, z = (p1.z + p2.z + p3.z) / 3;
    return triplet_point(x, y, z);
}
