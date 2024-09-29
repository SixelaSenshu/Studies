#include "../../headers/ReaderScene/ReaderScene.h"

#define READERSCENE_SIZE_BLOCK 5

static bool exception_shadow(char *buffer, ReaderScene *scene);
static bool exception_size(char *buffer, ReaderScene *scene);
static bool exception_name(char *buffer, ReaderScene *scene);
static bool exception_camera(char *buffer, ReaderScene *scene);
static bool exception_ambient(char *buffer, ReaderScene *scene);
static bool exception_diffuse(char *buffer, ReaderScene *scene);
static bool exception_specular(char *buffer, ReaderScene *scene);
static bool exception_shininess(char *buffer, ReaderScene *scene);
static bool exception_directional(char *buffer, ReaderScene *scene);
static bool exception_point(char *buffer, ReaderScene *scene);
static bool exception_vertex(char *buffer, ReaderScene *scene);
static bool exception_maxvertex(char *buffer, ReaderScene *scene);
static bool exception_spheres(char *buffer, ReaderScene *scene);
static bool exception_triangles(char *buffer, ReaderScene *scene);
static bool exception_plane(char *buffer, ReaderScene *scene);

extern ReaderScene *readerscene_create(char *filename)
{
    ReaderScene *scene = (ReaderScene *)malloc(sizeof(ReaderScene));
    if (!scene)
    {
        fprintf(stderr, "[ERREUR]Problème d'allocation de mémoire pour le lecteur de scène\n");
        goto error;
    }
    if (!readerscene_openfile(scene, filename))
        goto error;
    Triplet none = (Triplet){NONE, 0, 0, 0};
    scene->couleurs = tools_create_color(none, none, none, 0);
    if (!scene->couleurs)
    {
        fprintf(stderr, "[ERREUR]Problème d'allocation de mémoire pour le stockage des couleurs\n");
        goto error;
    }
    scene->triangles = (Triangle **)malloc(sizeof(Triangle *));
    if (!scene->triangles)
        goto error;
    scene->lights = (Light **)malloc(sizeof(Light *));
    if (!scene->lights)
        goto error;
    scene->planes = (Plane **)malloc(sizeof(Plane *));
    if (!scene->planes)
        goto error;
    scene->spheres = (Sphere **)malloc(sizeof(Sphere *));
    if (!scene->spheres)
        goto error;
    scene->filename = (char *)malloc(sizeof(char) * strlen("output.png") + 1);
    if (!scene->filename)
        goto error;
    scene->filename = "output.png\0";
    scene->sizePoints = 0;
    scene->sizePlanes = 0;
    scene->sizeSpheres = 0;
    scene->sizeTriangles = 0;
    scene->sizeLights = 0;
    scene->nbLights = 0;
    scene->nbPixels = 0;
    scene->nbPoints = 0;
    scene->nbSpheres = 0;
    scene->nbTriangles = 0;
    scene->nbPlanes = 0;
    scene->nbObjs = 0;
    scene->shadow = false;
    scene->height = 0;
    scene->width = 0;
    scene->points = NULL;
    scene->camera = NULL;
    return scene;
error:
    readerscene_destroy(scene);
    return NULL;
}

extern bool readerscene_openfile(ReaderScene *scene, char *filename)
{
    if (!scene)
    {
        return false;
    }
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        fprintf(stderr, "Couldn't open file %s\n", filename);
        return false;
    }
    scene->file = f;
    return true;
}

extern bool readerscene_quitfile(ReaderScene *scene)
{
    if (!scene)
    {
        return false;
    }
    if (fclose(scene->file) == EOF)
    {
        fprintf(stderr, "Couldn't close file %s\n", scene->filename);
        return false;
    }
    return true;
}

extern int readerscene_apply(ReaderScene *scene, char *object)
{
    if (!scene)
        return -1;
    if (!object || object[0] == '#')
    {
        return 0;
    }
    else if (!strncmp(object, "size", strlen("size")))
    {
        if (!exception_size(object, scene))
            goto error;
    }
    else if (!strncmp(object, "output", strlen("output")))
    {
        if (!exception_name(object, scene))
            goto warning;
    }
    else if (!strncmp(object, "camera", strlen("camera")))
    {
        if (!exception_camera(object, scene))
            goto error;
    }
    else if (!strncmp(object, "ambient", strlen("ambient")))
    {
        if (!exception_ambient(object, scene))
            goto error;
    }
    else if (!strncmp(object, "diffuse", strlen("diffuse")))
    {
        if (!exception_diffuse(object, scene))
            goto warning;
    }
    else if (!strncmp(object, "specular", strlen("specular")))
    {
        if (!exception_specular(object, scene))
            goto warning;
    }
    else if (!strncmp(object, "shininess", strlen("shininess")))
    {
        if (!exception_shininess(object, scene))
            goto warning;
    }
    else if (!strncmp(object, "directional", strlen("directional")))
    {
        if (!exception_directional(object, scene))
            goto error;
    }
    else if (!strncmp(object, "point", strlen("point")))
    {
        if (!exception_point(object, scene))
            goto error;
    }
    else if (!strncmp(object, "maxverts", strlen("maxverts")))
    {
        if (!exception_maxvertex(object, scene))
            goto error;
    }
    else if (!strncmp(object, "vertex", strlen("vertex")))
    {
        if (!exception_vertex(object, scene))
            goto error;
    }
    else if (!strncmp(object, "tri", strlen("tri")))
    {
        if (!exception_triangles(object, scene))
            goto error;
    }
    else if (!strncmp(object, "sphere", strlen("sphere")))
    {
        if (!exception_spheres(object, scene))
            goto error;
    }
    else if (!strncmp(object, "plane", strlen("plane")))
    {
        if (!exception_plane(object, scene))
            goto error;
    }
    else if (!strncmp(object, "shadow", strlen("shadow")))
    {
        if (!exception_shadow(object, scene))
            goto error;
    }
    else
    {
        goto error;
    }

    return 0;
error:
    return -1;
warning:
    return 2;
}

static bool exception_shadow(char *buffer, ReaderScene *scene)
{
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (!token)
    {
        fprintf(stderr, "[ERREUR] Erreur de saisie la valeur de l'ombre\n");
        return false;
    }
    if (!strcmp(token, "false") == 0)
        scene->shadow = false;
    if (!strcmp(token, "true") == 0)
        scene->shadow = true;
    return true;
}

static bool exception_size(char *buffer, ReaderScene *scene)
{
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (!token)
    {
        fprintf(stderr, "[ERREUR] Erreur de saisie de width pour l'image\n");
        return false;
    }
    scene->width = atoi(token);
    token = strtok(NULL, separator);
    if (!token)
    {
        fprintf(stderr, "[ERREUR] Erreur de saisie de heigth pour l'image\n");
        return false;
    }
    scene->height = atoi(token);
    scene->nbPixels = scene->height * scene->width;
    return true;
}

static bool exception_name(char *buffer, ReaderScene *scene)
{
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (token != NULL)
    {
        scene->filename = (char *)malloc(strlen(token) + 1);
        if (!scene->filename)
        {
            return false;
        }
        strcpy(scene->filename, token);
    }
    else
    {
        fprintf(stderr, "[WARNING] Erreur de saisie dans le nom du fichier\n");
    }
    return true;
}

static bool exception_camera(char *buffer, ReaderScene *scene)
{
    Triplet tp1, tp2, tp3;
    double d_cam1 = -1, d_cam2 = -1, d_cam3 = -1, value_f = -1;
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    if (token)
    {
        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam1 = atof(token);
        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam2 = atof(token);
        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam3 = atof(token);
        tp1 = (Triplet){VECTOR, d_cam1, d_cam2, d_cam3, true, true, true, true, true, false, true, true};

        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam1 = atof(token);
        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam2 = atof(token);
        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam3 = atof(token);
        tp2 = (Triplet){VECTOR, d_cam1, d_cam2, d_cam3, true, true, true, true, true, false, true, true};

        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam1 = atof(token);
        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam2 = atof(token);
        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        d_cam3 = atof(token);
        tp3 = (Triplet){VECTOR, d_cam1, d_cam2, d_cam3, true, true, true, true, true, false, true, true};

        token = strtok(NULL, separator);
        if (!token)
            goto errorToken;
        value_f = atof(token);

        scene->camera = tools_create_camera(tp1, tp2, tp3, value_f);
        if (!scene->camera)
        {
            fprintf(stderr, "[ERREUR] Erreur d'alocation de la caméra\n");
            return false;
        }
        token = NULL;
    }
    if (!scene->camera)
    {
        fprintf(stderr, "[ERREUR] Erreur d'alocation de la caméra ( manque de paramètre ou incorrect )\n");
        return false;
    }
    return true;
errorToken:
    fprintf(stderr, "[ERREUR]Manque de valeur : Erreur d'alocation de la caméra\n");
    return false;
}

static bool exception_ambient(char *buffer, ReaderScene *scene)
{
    double value_double1_ambiant = -1, value_double2_ambiant = -1, value_double3_ambiant = -1;
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double1_ambiant = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double2_ambiant = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double3_ambiant = atof(token);
    if (value_double1_ambiant > 1 || value_double2_ambiant > 1 || value_double3_ambiant > 1)
    {
        fprintf(stderr, "[ERREUR] Erreur d'alocation de la couleur ambiante (composante supérieur à 1) \n");
        return false;
    }

    scene->couleurs->ambiant->x = value_double1_ambiant;
    scene->couleurs->ambiant->y = value_double2_ambiant;
    scene->couleurs->ambiant->z = value_double3_ambiant;
    scene->couleurs->ambiant->type = COLOR;
    return true;
errorToken:
    fprintf(stderr, "[WARNING] Erreur d'allocation de la couleur ambiante (manque de paramètre) \n");
    return false;
}

static bool exception_diffuse(char *buffer, ReaderScene *scene)
{
    double value_double1_diffuse = 0, value_double2_diffuse = 0, value_double3_diffuse = 0;
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double1_diffuse = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double2_diffuse = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double3_diffuse = atof(token);
    if (value_double1_diffuse + scene->couleurs->ambiant->x > 1.0 || scene->couleurs->ambiant->y + value_double2_diffuse > 1 || value_double3_diffuse + scene->couleurs->ambiant->z > 1)
    {
        fprintf(stderr, "[ERREUR] Erreur d'alocation de la couleur diffuse (somme des composantes supérieur à 1) \n");
        return false;
    }
    scene->couleurs->diffuse->x = value_double1_diffuse;
    scene->couleurs->diffuse->y = value_double2_diffuse;
    scene->couleurs->diffuse->z = value_double3_diffuse;
    scene->couleurs->diffuse->type = COLOR;
    scene->hasdiffuse = true;
    return true;
errorToken:
    fprintf(stderr, "[WARNING] Erreur d'allocation de la couleur diffuse (manque de paramètre) \n");
    return true;
}

static bool exception_specular(char *buffer, ReaderScene *scene)
{
    double value_double1_specular = -1, value_double2_specular = -1, value_double3_specular = -1;
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double1_specular = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double2_specular = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double3_specular = atof(token);
    scene->couleurs->specular->x = value_double1_specular;
    scene->couleurs->specular->y = value_double2_specular;
    scene->couleurs->specular->z = value_double3_specular;
    scene->couleurs->specular->type = COLOR;
    return true;
errorToken:
    fprintf(stderr, "[WARNING] Erreur d'allocation de la couleur specular (manque de paramètre) \n");
    return true;
}

static bool exception_shininess(char *buffer, ReaderScene *scene)
{
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (!token)
    {
        fprintf(stderr, "[WARNING] Erreur d'alocation de la couleur shininnes : entrée invalide \n");
        return false;
    }

    scene->couleurs->shininess = atoi(token);
    return true;
}

static bool exception_directional(char *buffer, ReaderScene *scene)
{
    double double1, double2, double3;
    Triplet tp1 = (Triplet){NONE}, tp2 = (Triplet){NONE};
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    double1 = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    double2 = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    double3 = atof(token);
    tp1 = (Triplet){VECTOR, double1, double2, double3, true, true, true, true, true, false, true, true};

    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    double1 = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    double2 = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    double3 = atof(token);
    tp2 = (Triplet){
        COLOR,
        double1,
        double2,
        double3,
        true, false, true, false, false, true, false, false};

    if (!scene->lights || scene->nbLights == scene->sizeLights)
    {
        Light **newlistlights = (Light **)realloc(scene->lights, (scene->sizeLights + READERSCENE_SIZE_BLOCK) * sizeof(Light *));
        if (!newlistlights)
        {
            fprintf(stderr, "Couldn't create list of lights\n");
            return false;
        }
        scene->lights = newlistlights;
        scene->sizeLights += READERSCENE_SIZE_BLOCK;
    }
    Light *newLight = tools_create_light(LIGHT_DIRECTIONAL, (Triplet){}, tp1, tp2);
    if (!newLight)
    {
        fprintf(stderr, "Couldn't create lights\n");
        return false;
    }
    scene->lights[scene->nbLights] = newLight;
    scene->nbLights++;
    return true;
errorToken:
    fprintf(stderr, "[WARNING] Erreur d'allocation de la couleur lumière (manque de paramètre) \n");
    return false;
}

static bool exception_point(char *buffer, ReaderScene *scene)
{
    double value_double1, value_double2, value_double3;
    Triplet tp1 = (Triplet){NONE}, tp2 = (Triplet){NONE};
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double1 = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double2 = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double3 = atof(token);
    tp1 = (Triplet){POINT, value_double1, value_double2, value_double3, false, true, true, false, false, false, false, false};

    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double1 = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double2 = atof(token);
    token = strtok(NULL, separator);
    if (token == NULL)
        goto errorToken;
    value_double3 = atof(token);
    tp2 = (Triplet){COLOR, value_double1, value_double2, value_double3, true, false, true, false, false, true, false, false};
    if (!scene->lights || scene->nbLights == scene->sizeLights)
    {
        Light **newlistlights = (Light **)realloc(scene->lights, (scene->sizeLights + READERSCENE_SIZE_BLOCK) * sizeof(Light *));
        if (!newlistlights)
        {
            fprintf(stderr, "Couldn't create list of lights\n");
            return false;
        }
        scene->lights = newlistlights;
        scene->sizeLights = READERSCENE_SIZE_BLOCK;
    }
    Light *newLight = tools_create_light(LIGHT_POINT, tp1, (Triplet){NONE, 0, 0, 0}, tp2);
    if (!newLight)
    {
        fprintf(stderr, "Couldn't create lights\n");
        return false;
    }
    scene->lights[scene->nbLights] = newLight;
    scene->nbLights++;
    return true;
errorToken:
    fprintf(stderr, "[ERROR] Pas de token défini : annulation de la création de la lumière\n");
    return false;
}

static bool exception_maxvertex(char *buffer, ReaderScene *scene)
{
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (token == NULL)
    {
        fprintf(stderr, "[WARNING] Erreur d'allocation de maxvertex (manque de paramètre) \n");
        return false;
    }
    scene->sizePoints = atoi(token);
    return true;
}

static bool exception_vertex(char *buffer, ReaderScene *scene)
{
    double value_double1, value_double2, value_double3;
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double1 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double2 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double3 = atof(token);

    if (scene->sizePoints == 0)
    {
        fprintf(stderr, "[ERROR] Pas de maxvertex défini : annulation de la création du point\n");
        return true;
    }
    if (!scene->points)
    {
        Triplet **newlistspoints = (Triplet **)malloc(scene->sizePoints * sizeof(Triplet *));
        if (!newlistspoints)
        {
            fprintf(stderr, "Couldn't create list of points\n");
            return false;
        }
        scene->points = newlistspoints;
    }

    Triplet *newPoints = triplet_create_point(value_double1, value_double2, value_double3);
    if (!newPoints)
    {
        fprintf(stderr, "Couldn't create point\n");
        return false;
    }
    scene->points[scene->nbPoints++] = newPoints;
    return true;
errorToken:
    fprintf(stderr, "[ERROR] Pas de token défini : annulation de la création du point\n");
    return false;
}

static bool exception_spheres(char *buffer, ReaderScene *scene)
{

    double value_double1 = -1, value_double2 = -1, value_double3 = -1, value_double4;
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double1 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double2 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double3 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double4 = atof(token);

    if (!scene->spheres || scene->nbSpheres == scene->sizeSpheres)
    {
        Sphere **newlistspheres = (Sphere **)realloc(scene->spheres, (scene->sizeSpheres + READERSCENE_SIZE_BLOCK) * sizeof(Sphere *));
        if (!newlistspheres)
        {
            fprintf(stderr, "Couldn't create list of spheres\n");
            return false;
        }
        scene->spheres = newlistspheres;
        scene->sizeSpheres = scene->sizeSpheres + READERSCENE_SIZE_BLOCK;
    }
    Sphere *newSphere = tools_create_sphere((Triplet){POINT, value_double1, value_double2, value_double3, false, true, true, false, false, false, false, false}, value_double4, *(scene->couleurs->diffuse));
    if (!newSphere)
    {
        fprintf(stderr, "Couldn't create sphere\n");
        return false;
    }
    scene->spheres[scene->nbSpheres++] = newSphere;
    scene->nbObjs++;
    return true;
errorToken:
    fprintf(stderr, "[ERROR] Pas de token défini : annulation de la création de la sphère\n");
    return false;
}

static bool exception_triangles(char *buffer, ReaderScene *scene)
{
    int value_int1 = -1, value_int2 = -1, value_int3 = -1;
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_int1 = atoi(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_int2 = atoi(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_int3 = atoi(token);
    if (value_int1 > scene->sizePoints || value_int2 > scene->sizePoints || value_int3 > scene->sizePoints)
    {
        fprintf(stderr, "[ERROR] Nombre de point insuffisant ou paramètre incorrect pour la création du triangle.\n");
        return false;
    }
    if (!scene->triangles || scene->nbTriangles >= scene->sizeTriangles)
    {
        Triangle **newlisttriangles = (Triangle **)realloc(scene->triangles, (scene->sizeTriangles + READERSCENE_SIZE_BLOCK) * sizeof(Triangle));
        if (!newlisttriangles)
        {
            fprintf(stderr, "Couldn't create list of triangles\n");
            return false;
        }
        scene->triangles = newlisttriangles;
        scene->sizeTriangles = READERSCENE_SIZE_BLOCK;
    }
    Triangle *newTriangle = tools_create_triangle(*(scene)->points[value_int1], *(scene)->points[value_int2], *(scene)->points[value_int3], *(scene)->couleurs->diffuse);
    if (!newTriangle)
    {
        fprintf(stderr, "Couldn't create triangle\n");
        return false;
    }
    scene->triangles[scene->nbTriangles++] = newTriangle;
    scene->nbObjs++;
    return true;
errorToken:
    fprintf(stderr, "[ERROR] Pas de token défini : annulation de la création du triangle\n");
    return false;
}

static bool exception_plane(char *buffer, ReaderScene *scene)
{
    double value_double1, value_double2, value_double3;
    Triplet tp1 = (Triplet){NONE}, tp2 = (Triplet){NONE};
    const char *separator = " \n\r\t";
    char *token = strtok(buffer, separator);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double1 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double2 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double3 = atof(token);
    tp1 = (Triplet){POINT, value_double1, value_double2, value_double3, false, true, true, false, false, false, false, false};

    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double1 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double2 = atof(token);
    token = strtok(NULL, separator);
    if (!token)
        goto errorToken;
    value_double3 = atof(token);
    tp2 = (Triplet){VECTOR, value_double1, value_double2, value_double3, true, true, true, true, true, false, true, true};

    if (!scene->planes || scene->nbPlanes == scene->sizePlanes)
    {
        Plane **newlistplanes = (Plane **)realloc(scene->planes, (scene->sizePlanes + READERSCENE_SIZE_BLOCK) * sizeof(Plane *));
        if (!newlistplanes)
        {
            fprintf(stderr, "Couldn't create list of planes\n");
            return false;
        }
        scene->planes = newlistplanes;
        scene->sizePlanes = scene->sizePlanes + READERSCENE_SIZE_BLOCK;
    }
    Plane *newPlane = tools_create_plane(tp1, tp2);
    if (!newPlane)
    {
        fprintf(stderr, "Couldn't create plane\n");
        return false;
    }
    scene->planes[scene->nbPlanes] = newPlane;
    scene->nbPlanes++;
    return true;
errorToken:
    fprintf(stderr, "[ERROR] Pas de token défini : annulation de la création du plan\n");
    return false;
}

extern bool readerscene_readtext(ReaderScene *scene)
{
    if (!scene->file)
        return false;
    int res = 0;
    while (res != EOF)
    {
        res = readerscene_readline(scene);
        if (res == 0)
            return false;
    }
    return true;
}

extern int readerscene_readline(ReaderScene *scene)
{
    char buffer[300];
    int size_buffer = 0;
    int currentCharacter = fgetc(scene->file);
    while ((currentCharacter != '\n') && size_buffer < 300)
    {
        buffer[size_buffer++] = currentCharacter;
        currentCharacter = fgetc(scene->file);
    }
    buffer[size_buffer] = '\0';
    if (currentCharacter == EOF)
    {
        return EOF;
    }
    if (size_buffer != 0)
    {
        if (buffer[0] == '#' || buffer[0] == ' ' || buffer[0] == '\0' || buffer[0] == '\n')
            return 1;
        if (-1 == readerscene_apply(scene, buffer))
            return 0;
    }
    return 1;
}

extern void readerscene_destroy(ReaderScene *scene)
{
    if (scene != NULL)
    {
        int i;
        if (scene->camera != NULL)
            tools_destroy_camera(scene->camera);
        if (scene->couleurs != NULL)
            tools_destroy_color(scene->couleurs);
        if (scene->file != NULL)
            readerscene_quitfile(scene);
        // if (scene->filename != NULL)
        //     free(scene->filename);
        if (scene->planes != NULL)
        {
            for (i = 0; i < scene->nbPlanes; i++)
            {
                {
                    tools_destroy_plane(scene->planes[i]);
                }
            }
            free(scene->planes);
        }
        if (scene->triangles != NULL)
        {
            for (i = 0; i < scene->nbTriangles; i++)
            {
                {
                    tools_destroy_triangle(scene->triangles[i]);
                }
            }
            free(scene->triangles);
        }
        if (scene->spheres != NULL)
        {
            {
                for (i = 0; i < scene->nbSpheres; i++)
                {
                    tools_destroy_sphere(scene->spheres[i]);
                }
            }
            free(scene->spheres);
        }
        if (scene->points)
        {
            {
                for (i = 0; i < scene->nbPoints; i++)
                {
                    triplet_destroy(scene->points[i]);
                }
            }
            free(scene->points);
        }
        if (scene->lights)
        {
            {
                for (i = 0; i < scene->nbLights; i++)
                {
                    tools_destroy_light(scene->lights[i]);
                }
            }
            free(scene->lights);
        }
        free(scene);
    }
}

extern void readerscene_tostring(ReaderScene *scene, int choice)
{
    if (choice == 0)
    {

        if (scene)
        {
            int i;
            fprintf(stdout, "Filename : %s, Heigth : %d, Witdh :%d , MaxVertex : %d\n", scene->filename, scene->height, scene->width, scene->sizePoints);
            fprintf(stdout, "Lights : %d , Objs : %d , Pixels : %d , Point : %d , Spheres : %d , triangles : %d\n", scene->nbLights, scene->nbObjs, scene->nbPixels, scene->nbPoints, scene->nbSpheres, scene->nbTriangles);
            tools_to_string_camera(scene->camera);
            tools_to_string_color(scene->couleurs);
            for (i = 0; i < scene->nbTriangles; i++)
                tools_to_string_triangle(scene->triangles[i]);
            for (i = 0; i < scene->nbPoints; i++)
            {
                fprintf(stdout, "{Point :");
                triplet_display(*(scene->points[i]));
                fprintf(stdout, "}\n");
            }
            for (i = 0; i < scene->nbLights; i++)
                tools_to_string_light(scene->lights[i]);
            for (i = 0; i < scene->nbSpheres; i++)
                tools_to_string_sphere(scene->spheres[i]);
            for (i = 0; i < scene->nbPlanes; i++)
                tools_to_string_plane(scene->planes[i]);
        }
    }

    else
    {
        if (scene)
        {
            printf("%s\n", scene->filename);
            printf("%d\n", scene->nbPixels);
            printf("%d\n", scene->nbObjs);
            printf("%d\n", scene->nbLights);
        }
    }
}
