/**
 * @file Functions.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief Programme qui permet de manipuler toutes les fonctions pour la création des images
 * @date 1.01.2023
 * @version 1.0
 */
#ifndef _FUNCTION_H_
#define _FUNCTION_H_ 1

#include "Tools.h"

/**
 * @brief Structure permettant de récupérer un repère orthonormé pour une scène.
 *
 */
typedef struct _orthonormalMark
{
    Triplet u, //!< Vecteur U du repère orthonormé.
        v,     //!< Vecteur V du repère orthonormé.
        w;     //!< Vecteur W du repère orthonormé.
} OrthonormalMark;

/**
 * @brief Permet de récupérer les informations sur la réprésentation de la scène pour les pixels.
 *
 */
typedef struct _dimensionPixel
{
    double fovr,     //!< L'angle final.
        pixelHeight, //!< La hauteur du pixel.
        pixelWidth;  //!< La largeur du pixel.
    int width,       //!< La largeur de l'image.
        height;      //!< La hauteur de l'image.

} DimensionPixel;

/**
 * @brief Structure permettant de stocker toutes les informations en lien avec le discriminant.
 *
 */
typedef struct _delta
{
    double a, b, c;      //!< Les variables a b et c.
    double t1;           //!< Le point d'intersection final.
    double discriminant; //!< Le discriminant.
    int hasDiscriminant; //!< Si il y a un point d'intersection donc un discriminant > 0.
    Triplet point;       //!< Le point que l'on récupère via lookFrom & que l'on calcul avec le delta et le vecteru directionnel.
} Delta;

/**
 * @brief Permet de récupérer le repère orthonormé à partir des informations d'une scène.
 *
 * @param lookAt La position ou l'on regarde.
 * @param lookFrom La position ou l'on est.
 * @param up La direction ou on regarde.
 * @return une instance OrthonormalMark.
 */
extern OrthonormalMark orthonormal_mark(Triplet lookAt, Triplet lookFrom, Triplet up);

/**
 * @brief Permet de récupérer la dimension du pixel pour une scène.
 *
 * @param fieldOfView L'angle de Vue.
 * @param height La hauteur de l'image.
 * @param width La largeur de l'image.
 * @return une instance DimensionPixel.
 */
extern DimensionPixel dimension_pixel(double fieldOfView, int height, int width);

/**
 * @brief Permet de récupère le vecteur directionnel à partir d'une position
 *
 * @param dp Les dimensions des pixels.
 * @param mark Le répère orthonormé.
 * @param i Le point i sur l'image.
 * @param j Le point j sur l'image.
 * @return Une instance de Triplet.
 */
extern Triplet directional_vector_p(DimensionPixel dp, OrthonormalMark mark, int i, int j);

/**
 * @brief Permet de récupère le point d'intersection pour une sphère à partir des données d'une scène et du point.
 *
 * @param direction Le vecteur direction du point.
 * @param center Le point du centre de la sphère.
 * @param radius Le rayon de la sphère.
 * @param lookFrom La position ou l'on est.
 * @return Une instance de Delta.
 */
extern Delta inter_radius_sphere(Triplet direction, Triplet center, double radius, Triplet lookFrom);
#endif
