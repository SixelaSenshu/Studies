#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_ 1

#include "Functions.h"
/**
 * @brief Donne le point d'intersection pour un plan à partir d'une direction et d'un point de vue.
 *
 * @param lookFrom La direction de ou on regarde.
 * @param direction Le vecteur directionnel.
 * @param pointplane Le point du plan.
 * @param vectorplane Le vecteur du plan.
 * @return double
 */
extern double intersection_plane(Triplet lookFrom, Triplet direction, Triplet pointplane, Triplet vectorplane);

/**
 * @brief Donne le point à partir de l'intersection d'un PDV vers un plan.
 *
 * @param lookFrom La direction de ou on regarde.
 * @param direction Le vecteur directionnel.
 * @param plane Le plan que l'on examine.
 * @return Le point.
 */
extern Triplet get_point_in_plane(Triplet lookFrom, Triplet direction, Plane plane);

/**
 * @brief Donne la normal d'un triangle.
 *
 * @param a Le point a du triangle.
 * @param b Le point b du triangle.
 * @param c Le point c du triangle.
 * @return Triplet
 */
extern Triplet normal_of_triangle(Triplet a, Triplet b, Triplet c);

/**
 * @brief Vérifie si un point est dans un trianlge
 *
 * @param a Le point a du triangle.
 * @param b Le point b du triangle.
 * @param c Le point c du triangle.
 * @param point Le point que l'on gagne
 * @return true
 * @return false
 */
extern bool point_in_triangle(Triplet a, Triplet b, Triplet c, Triplet point);

/**
 * @brief Get the gravity point triangle object
 *
 * @param p1
 * @param p2
 * @param p3
 * @return Triplet
 */
extern Triplet get_gravity_point_triangle(Triplet p1, Triplet p2, Triplet p3);

#endif
