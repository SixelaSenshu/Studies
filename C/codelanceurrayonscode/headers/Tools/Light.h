/**
 * @file Light.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief Programme qui permet de manipuler toutes les fonctions en lien avec la lumière pour la création des images
 * @date 1.01.2023
 * @version 1.0
 */
#ifndef _LIGHT_H_
#define _LIGHT_H_ 1

#include "Functions.h"
#include "../Raytrace/Raytrace.h"
#include "../ReaderScene/ReaderScene.h"

/**
 * @brief Permet de caclculer la norme pour la direction d'un cercle vers un point.
 *
 * @param p Le point ou se dirige la sphère.
 * @param cc Le centre de la sphère.
 * @return un Triplet.
 */
extern Triplet get_normal_radius(Triplet p, Triplet cc);

/**
 * @brief Calcul la direction de la lumière de type direction.
 *
 * @param position La position de la lumière.
 * @param color La couleur de la lumière.
 * @param point Le point d'intersection de la sphère.
 * @return un Triplet.
 */
extern Triplet light_with_direction(Triplet position, Triplet color, Triplet point);

/**
 * @brief Calcul la direction de la lumière de type point.
 *
 * @param position La position de la lumière.
 * @param color La couleur de la lumière.
 * @param point Le point d'intersection de la sphère.
 * @return un Triplet
 */
extern Triplet light_with_point(Triplet position, Triplet color, Triplet point);

/**
 * @brief Calcul la somme des lumières.
 *
 * @param point Le point de l'objet
 * @param light Les lumières.
 * @param p Le point d'intersection.
 * @param nbLights Le nombre de lumière.
 * @param scene La scene.
 * @return un Triplet
 */
extern Triplet get_sum_colors(Triplet point, Light **light, Triplet p, int nbLights, ReaderScene *scene, int i, int j);

/**
 * @brief
 *
 * @param point Le point de l'objet
 * @param light Les lumières.
 * @param p Le point d'intersection.
 * @param nbLights Le nombre de lumière.
 * @param ambiant La lumière ambiante
 * @param diffuse La limière de l'objet
 * @param scene La scene
 * @return un Triplet
 */
extern Triplet get_final_color(Triplet point, Light **light, Triplet p, int nbLights, Triplet ambiant, Triplet diffuse, ReaderScene *scene, int i, int j);

#endif