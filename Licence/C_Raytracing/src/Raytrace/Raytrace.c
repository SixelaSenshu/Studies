#include "../../headers/Raytrace/Raytrace.h"

extern bool raytrace_planes_calculs(ReaderScene *scene, RaytraceCalcul *data)
{
    if (!scene || !data)
    {
        return false;
    }
    int k;
    for (k = 0; k < scene->nbPlanes; k++)
    {
        data->intersectionTemp = intersection_plane(data->lookFrom, data->direction, scene->planes[k]->point, scene->planes[k]->vector);
        if (data->intersectionTemp != -1 && ((data->finalintersection > data->intersectionTemp && data->finalintersection >= 0) || data->finalintersection <= 0))
        {
            data->intersectionPlane = data->intersectionTemp;
            data->currentIndPlane = k;
        }
    }
    if ((data->finalintersection > data->intersectionTriangle && data->intersectionTriangle > 0) || data->finalintersection < 0)
    {
        data->currentIntersection = 0;
        data->beforeintersection = data->finalintersection;
        data->finalintersection = data->intersectionPlane;
    }
    return true;
}

extern bool raytrace_triangles_calculs(ReaderScene *scene, RaytraceCalcul *data)
{
    if (!scene || !data)
    {
        return false;
    }
    Triplet pointTri, new;
    int h;
    for (h = 0; h < scene->nbTriangles; h++)
    {
        Triplet normal = normal_of_triangle(scene->triangles[h]->point1, scene->triangles[h]->point2, scene->triangles[h]->point3);
        pointTri = scene->triangles[h]->point1;
        data->intersectionTemp = intersection_plane(data->lookFrom, data->direction, pointTri, normal);
        if (data->intersectionTemp != -1 && ((data->finalintersection > data->intersectionTemp && data->finalintersection >= 0) || data->finalintersection <= 0))
        {
            new = get_point_in_plane(data->lookFrom, data->direction, (Plane){pointTri, normal});
            triplet_sub(&new, &pointTri);
            if (point_in_triangle(scene->triangles[h]->point1, scene->triangles[h]->point2, scene->triangles[h]->point3, new))
            {
                data->currentIndTriangle = h;
                data->intersectionTriangle = data->intersectionTemp;
                data->intersection = new;
            }
        }
    }

    if ((data->finalintersection > data->intersectionTriangle && data->intersectionTriangle > 0) || data->finalintersection < 0)
    {
        data->currentIntersection = 2;
        data->beforeintersection = data->finalintersection;
        data->finalintersection = data->intersectionTriangle;
    }
    return true;
}

extern bool raytrace_spheres_calculs(ReaderScene *scene, RaytraceCalcul *data)
{
    if (!scene || !data)
    {
        return false;
    }
    Delta current = (Delta){0, 0, 0, -1, 0, 0, (Triplet){NONE}}, next;
    int h;
    for (h = 0; h < scene->nbSpheres; h++)
    {
        next = inter_radius_sphere(data->direction, scene->spheres[h]->center, scene->spheres[h]->radius, data->lookFrom);
        if (next.t1 >= 0 && ((next.t1 < current.t1 && current.t1 >= 0) || (current.t1 < 0)))
        {
            current = next;
            data->currentIndSphere = h;
            data->intersectionSphere = current.t1;
        }
    }

    if ((data->finalintersection > data->intersectionSphere && data->intersectionSphere > 0) || data->finalintersection < 0)
    {
        data->beforeintersection = data->finalintersection;
        data->finalintersection = data->intersectionSphere;
        data->currentIntersection = 1;
        data->intersection = current.point;
    }
    return true;
}

extern bool raytrace_basic_calculations(ReaderScene *scene, RaytraceCalcul *data, int i, int j)
{
    if (!scene || !data)
    {
        return false;
    }
    data->mark = orthonormal_mark(data->lookAt, data->lookFrom, data->lookUp);
    data->dim = dimension_pixel(scene->camera->degree, scene->height, scene->width);
    data->direction = directional_vector_p(data->dim, data->mark, i, j);
    return true;
}

extern RaytraceCalcul *raytrace_create_data(Triplet lookFrom, Triplet lookAt, Triplet lookUp)
{
    RaytraceCalcul *data = (RaytraceCalcul *)malloc(sizeof(RaytraceCalcul));
    if (data == NULL)
    {
        fprintf(stderr, "error to allocate raytracecalcul\n");
        return NULL;
    }
    data->beforeintersection = -1;
    data->lookFrom = lookAt;
    data->lookAt = lookFrom;
    data->lookUp = lookUp;
    data->direction = (Triplet){VECTOR, 0, 0, 0};
    data->point = (Triplet){POINT, 0, 0, 0};
    data->color = (Triplet){COLOR, 0, 0, 0};
    data->intersection = (Triplet){POINT, 0, 0, 0};
    data->currentIndSphere = -1;
    data->currentIndTriangle = -1;
    data->currentIntersection = -1;
    data->currentIntersection = -1;
    data->intersectionTriangle = -1;
    data->intersectionSphere = -1;
    data->intersectionPlane = -1;
    data->intersectionTemp = -1;
    data->finalintersection = -1;
    return data;
}

extern void raytrace_destroy_data(RaytraceCalcul *data)
{
    if (data != NULL)
    {
        free(data);
    }
}

extern Triplet raytrace_couleur_p_intersertion(ReaderScene *scene, int i, int j)
{
    Triplet new, normalres, finalcolor;
    if (!scene)
        return (Triplet){COLOR, 0, 0, 0, true, false, true, false, false, true, false, false};
    RaytraceCalcul *raytraceData = raytrace_create_data(scene->camera->lookAt, scene->camera->lookFrom, scene->camera->up);
    RaytraceCalcul *dataReverse;
    if (!raytraceData)
        return (Triplet){NONE};
    raytrace_basic_calculations(scene, raytraceData, i, j);
    raytrace_planes_calculs(scene, raytraceData);
    raytrace_spheres_calculs(scene, raytraceData);
    raytrace_triangles_calculs(scene, raytraceData);

    if (raytraceData->currentIntersection == 2 && raytraceData->currentIndTriangle >= 0)
    {
        raytraceData->color = scene->triangles[raytraceData->currentIndTriangle]->color;
        raytraceData->point = scene->triangles[raytraceData->currentIndTriangle]->point1;
        normalres = normal_of_triangle(raytraceData->point, scene->triangles[raytraceData->currentIndTriangle]->point2, scene->triangles[raytraceData->currentIndTriangle]->point3);
        new = get_point_in_plane(raytraceData->lookFrom, raytraceData->direction, (Plane){raytraceData->point, normalres});
        raytraceData->intersection = new;
    }
    else if (raytraceData->currentIntersection == 1 && raytraceData->currentIndSphere >= 0)
    {
        raytraceData->color = scene->spheres[raytraceData->currentIndSphere]->color;
        raytraceData->point = scene->spheres[raytraceData->currentIndSphere]->center;
    }
    else
        return (Triplet){COLOR, 0, 0, 0, true, false, true, false, false, true, false, false};
    finalcolor = raytraceData->color;

    if (scene->nbLights > 0)
    {
        finalcolor = get_final_color(raytraceData->point, scene->lights, raytraceData->intersection, scene->nbLights, *(scene->couleurs->ambiant), raytraceData->color, scene, i, j);
    }
    else if (!scene->hasdiffuse || scene->nbLights == 0)
        finalcolor = *(scene->couleurs->ambiant);
    raytrace_destroy_data(raytraceData);
    return finalcolor;
}

extern bool raytrace_create_image(ReaderScene *scene)
{
    Triplet d;

    FIBITMAP *img = FreeImage_Allocate(scene->width, scene->height, 24, 0, 0, 0);
    RGBQUAD color;
    if (!img)
    {
        fprintf(stderr, "[Allocate] Problème d'allocation d'image\n");
        goto error;
    }

    BYTE xb, yb, zb;
    for (int i = 0; i < scene->width; i++)
    {
        for (int j = 0; j < scene->height; j++)
        {
            xb = 0xff;
            yb = 0xff;
            zb = 0xff;
            d = raytrace_couleur_p_intersertion(scene, i, j);
            color.rgbRed = xb * d.x + 0.5;
            color.rgbGreen = yb * d.y + 0.5;
            color.rgbBlue = zb * d.z + 0.5;
            color.rgbReserved = 1;
            FreeImage_SetPixelColor(img, i, j, &color);
        }
    }
    FreeImage_Save(FIF_PNG, img, scene->filename, 0);
    FreeImage_Unload(img);
    return true;
error:
    FreeImage_Unload(img);
    return false;
}
