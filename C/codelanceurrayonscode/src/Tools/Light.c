#include "../../headers/Tools/Light.h"

extern Triplet get_normal_radius(Triplet p, Triplet cc)
{
    Triplet n = (Triplet){VECTOR, p.x, p.y, p.z, true, true, true, true, true, false, true, true};
    triplet_sub(&n, &cc);
    triplet_normalization(&n);
    return n;
}

extern Triplet light_with_direction(Triplet position, Triplet color, Triplet point)
{
    Triplet ldir = (Triplet){VECTOR, position.x, position.y, position.z, true, true, true, true, true, false, true, true};
    triplet_normalization(&ldir);
    return ldir;
}

extern Triplet light_with_point(Triplet position, Triplet color, Triplet point)
{
    Triplet ldir = (Triplet){POINT, position.x, position.y, position.z, true, true, true, true, true, false, true, true};
    triplet_sub(&ldir, &point);
    triplet_normalization(&ldir);
    return ldir;
}
extern Triplet get_sum_colors(Triplet point, Light **light, Triplet p, int nbLights, ReaderScene *scene, int i, int j)
{
    RaytraceCalcul *dataReverse;
    Triplet sumColor = (Triplet){COLOR, 0.0, 0.0, 0.0, true, false, true, false, false, true, false, false};
    double scal = 0;
    Triplet n;
    n = get_normal_radius(p, point);
    Triplet ldir, lcolor;
    for (int i = 0; i < nbLights; i++)
    {
        scal = 0;
        if (light[i]->type == LIGHT_DIRECTIONAL)
        {
            ldir = light_with_direction(light[i]->direction, light[i]->color, p);
            scal = triplet_scalar_product(&ldir, &n);
        }
        else if (light[i]->type == LIGHT_POINT)
        {
            ldir = light_with_point(light[i]->point, light[i]->color, p);
            scal = triplet_scalar_product(&ldir, &n);
        }
        if (scal >= 0.0)
        {
            if (scene->shadow)
            {
                dataReverse = raytrace_create_data(p, ldir, scene->camera->up);
                if (!dataReverse)
                {
                    return (Triplet){NONE};
                }
                raytrace_basic_calculations(scene, dataReverse, i, j);
                raytrace_planes_calculs(scene, dataReverse);
                raytrace_spheres_calculs(scene, dataReverse);
                raytrace_triangles_calculs(scene, dataReverse);
                if (dataReverse->finalintersection >= 0)
                {
                    lcolor = (Triplet){COLOR, light[i]->color.x, light[i]->color.y, light[i]->color.z, true, false, true, false, false, true, false, false};
                    triplet_mul(&lcolor, scal);
                    triplet_add(&sumColor, &lcolor);
                }
                raytrace_destroy_data(dataReverse);
            }
            else
            {
                lcolor = (Triplet){COLOR, light[i]->color.x, light[i]->color.y, light[i]->color.z, true, false, true, false, false, true, false, false};
                triplet_mul(&lcolor, scal);
                triplet_add(&sumColor, &lcolor);
            }
        }
    }
    return sumColor;
}

extern Triplet get_final_color(Triplet point, Light **light, Triplet p, int nbLights, Triplet ambiant, Triplet diffuse, ReaderScene *scene, int i, int j)
{
    Triplet sumcolor = get_sum_colors(point, light, p, nbLights, scene, i, j);
    triplet_schur(&sumcolor, &diffuse);
    triplet_add(&sumcolor, &ambiant);
    return sumcolor;
}