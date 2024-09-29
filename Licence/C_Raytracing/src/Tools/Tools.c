#include "../../headers/Tools/Tools.h"

extern Camera *tools_create_camera(Triplet lookFrom, Triplet lookAt, Triplet up, double degree)
{
    Camera *camera = NULL;

    camera = (Camera *)malloc(sizeof(Camera));
    if (!camera)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation de la caméra\n");
        goto error;
    }
    camera->lookAt = lookAt;
    camera->lookFrom = lookFrom;
    camera->up = up;
    camera->degree = degree;
    return camera;
error:
    return NULL;
}

extern void tools_destroy_camera(Camera *camera)
{
    if (camera)
    {
        free(camera);
    }
}

extern Color *tools_create_color(Triplet ambiant, Triplet diffuse, Triplet specular, int shininess)
{
    Color *color = NULL;
    Triplet *newAmbiant = NULL, *newDiffuse = NULL, *newSpecular = NULL;

    color = (Color *)malloc(sizeof(Color));
    if (!color)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation de la couleur\n");
        goto error;
    }
    newAmbiant = triplet_create_color(ambiant.x, ambiant.y, ambiant.z);
    if (!newAmbiant)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation de la couleur\n");
        goto error;
    }
    newDiffuse = triplet_create_color(diffuse.x, diffuse.y, diffuse.z);
    if (!newDiffuse)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation de la couleur\n");
        goto error;
    }
    newSpecular = triplet_create_color(specular.x, specular.y, specular.z);
    if (!newSpecular)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation de la couleur\n");
        goto error;
    }
    color->ambiant = newAmbiant;
    color->diffuse = newDiffuse;
    color->specular = newSpecular;
    color->shininess = shininess;
    return color;
error:
    if (newAmbiant)
        free(newAmbiant);
    if (newDiffuse)
        free(newDiffuse);
    if (newSpecular)
        free(newSpecular);
    if (color)
        free(color);
    return NULL;
}

extern void tools_destroy_color(Color *color)
{
    if (color)
    {
        if (color->ambiant)
            free(color->ambiant);
        if (color->diffuse)
            free(color->diffuse);
        if (color->specular)
            free(color->specular);
        free(color);
    }
}

extern Light *tools_create_light(TypeLight type, Triplet point, Triplet direction, Triplet color)
{
    Light *ligth = NULL;

    ligth = (Light *)malloc(sizeof(Light));
    if (!ligth)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation de la camlumièreéra\n");
        goto error;
    }
    if (type == LIGHT_DIRECTIONAL)
    {
        ligth->direction = direction;
    }
    else if (type == LIGHT_POINT)
    {
        ligth->point = point;
    }
    else
    {
        goto error;
    }
    ligth->color = color;
    ligth->type = type;
    return ligth;
error:
    if (ligth)
        free(ligth);
    return NULL;
}

extern void tools_destroy_light(Light *light)
{
    if (light)
    {
        free(light);
    }
}

extern Sphere *tools_create_sphere(Triplet center, double radius, Triplet color)
{
    Sphere *sphere = NULL;

    sphere = (Sphere *)malloc(sizeof(Sphere));
    if (!sphere)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation de la sphere\n");
        goto error;
    }
    sphere->color = color;
    sphere->center = center;
    sphere->radius = radius;
    return sphere;
error:
    return NULL;
}

extern void tools_destroy_sphere(Sphere *sphere)
{
    if (sphere)
    {
        free(sphere);
    }
}

extern Triangle *tools_create_triangle(Triplet point1, Triplet point2, Triplet point3, Triplet color)
{
    Triangle *triangle = NULL;

    triangle = (Triangle *)malloc(sizeof(Triangle));
    if (!triangle)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation du triangle\n");
        goto error;
    }
    triangle->color = color;
    triangle->point1 = point1;
    triangle->point2 = point2;
    triangle->point3 = point3;
    return triangle;
error:
    return NULL;
}

extern void tools_destroy_triangle(Triangle *triangle)
{
    if (triangle)
    {
        free(triangle);
    }
}

extern Plane *tools_create_plane(Triplet point, Triplet vector)
{
    Plane *plan = NULL;

    plan = (Plane *)malloc(sizeof(Plane));
    if (!plan)
    {
        fprintf(stderr, "[ERREUR] Echec pour l'allocation du plan\n");
        goto error;
    }
    plan->point = point;
    plan->vector = vector;
    return plan;
error:
    return NULL;
}

extern void tools_destroy_plane(Plane *plane)
{
    if (plane)
    {
        free(plane);
    }
}

extern void tools_to_string_camera(Camera *camera)
{
    if (camera)
    {
        fprintf(stdout, "{camera :\n");
        fprintf(stdout, "look from :");
        triplet_display(camera->lookFrom);
        fprintf(stdout, "look at :");
        triplet_display(camera->lookAt);
        fprintf(stdout, "up :");
        triplet_display(camera->up);
        fprintf(stdout, "degree:%f\n", camera->degree);
        fprintf(stdout, "}\n");
    }
    else
    {
        fprintf(stdout, "Can't find camera\n");
    }
}
extern void tools_to_string_color(Color *color)
{
    if (color)
    {
        fprintf(stdout, "{color :\n");
        fprintf(stdout, "ambiant :");
        triplet_display(*(color->ambiant));
        fprintf(stdout, "diffuse :");
        triplet_display(*(color->diffuse));
        fprintf(stdout, "specular :");
        triplet_display(*(color->specular));
        fprintf(stdout, "shininess : %d\n", color->shininess);
        fprintf(stdout, "}\n");
    }
    else
    {
        fprintf(stdout, "Can't find color\n");
    }
}
extern void tools_to_string_light(Light *light)
{
    if (light)
    {
        fprintf(stdout, "{light :\n");
        fprintf(stdout, "color :");
        triplet_display(light->color);
        if (light->type == LIGHT_POINT)
        {
            fprintf(stdout, "type: point :");
            triplet_display(light->point);
        }
        if (light->type == LIGHT_DIRECTIONAL)
        {
            fprintf(stdout, "type: direction :");
            triplet_display(light->direction);
        }
        fprintf(stdout, "}\n");
    }
    else
    {
        fprintf(stdout, "Can't find light\n");
    }
}
extern void tools_to_string_sphere(Sphere *sphere)
{
    if (sphere)
    {
        fprintf(stdout, "{sphere :\n");
        fprintf(stdout, "center :");
        triplet_display(sphere->center);
        fprintf(stdout, "color :");
        triplet_display(sphere->color);
        fprintf(stdout, "radius:%f\n", sphere->radius);
        fprintf(stdout, "}\n");
    }
    else
    {
        fprintf(stdout, "Can't find sphere\n");
    }
}
extern void tools_to_string_triangle(Triangle *triangle)
{
    if (triangle)
    {
        fprintf(stdout, "{triangle :\n");
        fprintf(stdout, "color :");
        triplet_display(triangle->color);
        fprintf(stdout, "point1 :");
        triplet_display(triangle->point1);
        fprintf(stdout, "point2 :");
        triplet_display(triangle->point2);
        fprintf(stdout, "point3 :");
        triplet_display(triangle->point3);
        fprintf(stdout, "}\n");
    }
    else
    {
        fprintf(stdout, "Can't find triangle\n");
    }
}
extern void tools_to_string_plane(Plane *plane)
{
    if (plane)
    {
        fprintf(stdout, "{Plane :\n");
        fprintf(stdout, "point :");
        triplet_display(plane->point);
        fprintf(stdout, "vector :");
        triplet_display(plane->vector);
        fprintf(stdout, "}\n");
    }
    else
    {
        fprintf(stdout, "Can't find plane\n");
    }
}
