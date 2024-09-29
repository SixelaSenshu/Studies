#include "../../headers/Tools/Functions.h"

extern OrthonormalMark orthonormal_mark(Triplet lookAt, Triplet lookFrom, Triplet up)
{
    OrthonormalMark mark = {};
    Triplet wnew, upnew, vnew;
    wnew = (Triplet){VECTOR, lookFrom.x, lookFrom.y, lookFrom.z, true, true, true, true, true, false, true, true};
    upnew = (Triplet){VECTOR, up.x, up.y, up.z, true, true, true, true, true, false, true, true};
    triplet_sub(&wnew, &lookAt);
    triplet_normalization(&wnew);
    triplet_vectorial_product(&upnew, &wnew);
    triplet_normalization(&upnew);
    vnew = (Triplet){VECTOR, wnew.x, wnew.y, wnew.z, true, true, true, true, true, false, true, true};
    triplet_vectorial_product(&vnew, &upnew);
    triplet_normalization(&vnew);
    mark.w = wnew;
    mark.u = upnew;
    mark.v = vnew;
    return mark;
}

extern DimensionPixel dimension_pixel(double fieldOfView, int height, int width)
{

    DimensionPixel dim;
    dim.fovr = ((M_PI * fieldOfView) / 180.0);
    dim.pixelHeight = tan(dim.fovr / 2.0);
    dim.pixelWidth = dim.pixelHeight * ((double)width / (double)height);
    dim.width = width;
    dim.height = height;
    return dim;
}

extern Triplet directional_vector_p(DimensionPixel dp, OrthonormalMark mark, int i, int j)
{
    double a, b, diva, divb, upa, upb;
    divb = (double)dp.height / 2;
    diva = (double)dp.width / 2;
    upa = dp.pixelWidth * (i - diva + 0.5);
    upb = dp.pixelHeight * (j - divb + 0.5);
    a = upa / diva;
    b = upb / divb;
    Triplet u, v, w;
    u = (Triplet){VECTOR, mark.u.x, mark.u.y, mark.u.z, true, true, true, true, true, false, true, true};
    v = (Triplet){VECTOR, mark.v.x, mark.v.y, mark.v.z, true, true, true, true, true, false, true, true};
    w = (Triplet){VECTOR, mark.w.x, mark.w.y, mark.w.z, true, true, true, true, true, false, true, true};

    triplet_mul(&u, a);
    triplet_mul(&v, b);
    triplet_sub(&v, &w);
    triplet_add(&u, &v);
    triplet_normalization(&u);
    mark.u = u;
    mark.v = v;
    mark.w = w;
    return mark.u;
}

extern Delta inter_radius_sphere(Triplet direction, Triplet center, double radius, Triplet lookFrom)
{
    Delta delta;
    double t1, t2;

    // a = 1
    delta.a = triplet_scalar_product(&direction, &direction);

    // c = (o - cc) . (o - cc) - r²
    Triplet diff_o_cc = (Triplet){VECTOR, lookFrom.x, lookFrom.y, lookFrom.z, true, true, true, true, true, false, true, true};
    triplet_sub(&diff_o_cc, &center);
    delta.c = triplet_scalar_product(&diff_o_cc, &diff_o_cc) - (radius * radius);
    delta.b = triplet_scalar_product(&diff_o_cc, &direction) * 2;
    delta.discriminant = (delta.b * delta.b) - (4 * delta.a * delta.c);
    delta.point = (Triplet){POINT, lookFrom.x, lookFrom.y, lookFrom.z, false, true, true, false, false, false, false, false};
    if (delta.discriminant > 0)
    {
        delta.hasDiscriminant = 1;
        t1 = (-delta.b + sqrt(delta.discriminant)) / 2 * delta.a;
        t2 = (-delta.b - sqrt(delta.discriminant)) / 2 * delta.a;
        if (t2 > 0)
            delta.t1 = t2;
        else if (t1 > 0)
            delta.t1 = t1;
        else
        {
            delta.hasDiscriminant = 0;
            delta.t1 = -1;
        }
    }
    else if (0 == delta.discriminant)
    {
        delta.t1 = -delta.b / 2 * delta.a;
        delta.hasDiscriminant = 1;
    }
    else
    {
        delta.t1 = -1;
        delta.hasDiscriminant = 0;
        delta.point = (Triplet){NONE, 0, 0, 0};
    }
    if (delta.hasDiscriminant > 0)
    {
        triplet_mul(&direction, delta.t1);
        triplet_add(&delta.point, &direction);
    }
    return delta;
}
