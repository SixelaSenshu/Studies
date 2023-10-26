
/**
 * @file Raytrace.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief outils permettant de creer un compateur qui permet de comparer deux images et de créer la différence.
 * @date 1.01.2023
 * @version 1.0
 */
#ifndef _Raytrace_H_
#define _Raytrace_H_ 1

#include "../../lib/FreeImage/Source/FreeImage.h"
#include "../ReaderScene/ReaderScene.h"
#include "../Tools/Light.h"
#include "../Tools/Triangle.h"

typedef struct raytracecalcul
{
    OrthonormalMark mark;
    DimensionPixel dim;
    Triplet lookFrom;
    Triplet lookAt;
    Triplet lookUp;
    Triplet direction;
    Triplet point;
    Triplet color;
    Triplet intersection;
    int currentIndSphere;
    int currentIndTriangle;
    int currentIntersection;
    int currentIndPlane;
    double intersectionTriangle;
    double intersectionSphere;
    double intersectionPlane;
    double intersectionTemp;
    double finalintersection;
    double beforeintersection;
} RaytraceCalcul;

/**
 * @brief
 *
 * @param lookFrom
 * @param lookAt
 * @param lookUp
 * @return RaytraceCalcul*
 */
extern RaytraceCalcul *raytrace_create_data(Triplet lookFrom, Triplet lookAt, Triplet lookUp);

/**
 * @brief
 *
 * @param data
 */
extern void raytrace_destroy_data(RaytraceCalcul *data);

/**
 * @brief
 *
 * @param scene
 * @param data
 * @return true
 * @return false
 */
extern bool raytrace_planes_calculs(ReaderScene *scene, RaytraceCalcul *data);

/**
 * @brief
 *
 * @param scene
 * @param data
 * @return true
 * @return false
 */
extern bool raytrace_triangles_calculs(ReaderScene *scene, RaytraceCalcul *data);

/**
 * @brief
 *
 * @param scene
 * @param data
 * @return true
 * @return false
 */
extern bool raytrace_spheres_calculs(ReaderScene *scene, RaytraceCalcul *data);

/**
 * @brief
 *
 * @param scene
 * @param data
 * @param i
 * @param j
 * @return true
 * @return false
 */
extern bool raytrace_basic_calculations(ReaderScene *scene, RaytraceCalcul *data, int i, int j);

/**
 * @brief Permet de récupérer la couleur du pixel sur l'image par rapport au information d'une scène.
 *
 * @param scene La scène en question.
 * @param i La position i.
 * @param j La position j.
 * @return L'instance Triplet qui est la couleur.
 */
extern Triplet raytrace_couleur_p_intersertion(ReaderScene *scene, int i, int j);

/**
 * @brief Permet de créer une couleur en 2 dimensions.
 *
 * @param scene La scène en question.
 * @return true
 * @return false
 */
extern bool raytrace_create_image(ReaderScene *scene);

#endif
