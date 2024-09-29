/**
 * @file Triplet.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief Programme qui permet de manipuler une bibiothèque mathématique sur les différents type de triplet : Vecteur, Point et Couleur.
 * Le programme contient des fonctions d'allocation, de désallocation, d'affichage et d'opérations sur ces triplets.
 * @date 1.01.2023
 * @version 1.0
 */

#ifndef _TRIPLET_H_
#define _TRIPLET_H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/**
 * @brief Types des triplet
 */
typedef enum type
{
    POINT,  //!< Triplet de type point.
    VECTOR, //!< Triplet de type vecteur.
    COLOR,  //!< Triplet de type couleur.
    NONE    //!< Triplet de type null.
} Type;

/**
 * @brief Structure de type triplet qui permet de manipuler différents types ( Vecteur , Point et Couleur )
 * @param type Enumération permettant de comparer les différents types de triples.
 * @param x La valeur x du triplet.
 * @param y La valeur y du triplet.
 * @param z La valeur z du triplet.
 * @param add L'autorisation de l'opération add sur le triplet
 * @param sub L'autorisation de l'opération sub sur le triplet
 * @param mul L'autorisation de l'opération mul sur le triplet
 * @param scalProd L'autorisation de l'opération scalProd sur le triplet
 * @param vectProd L'autorisation de l'opération vectProd sur le triplet
 * @param schurProd L'autorisation de l'opération schurProd sur le triplet
 * @param length L'autorisation de l'opération length sur le triplet
 * @param normalization L'autorisation de l'opération normalization sur le triplet
 */
typedef struct triplet
{
    Type type;
    double x, y, z;
    bool add, sub, mul, scalProd, vectProd, schurProd, length, normalization;
} Triplet;

/**
 * @brief Permet de générer un triplet de type Point avec ces autorisations.
 * @param x La valeur x du triplet.
 * @param y La valeur y du triplet.
 * @param z La valeur z du triplet.
 * @return un point.
 */
extern Triplet *triplet_create_point(double x, double y, double z);

/**
 * @brief Permet de générer un triplet de type Vecteur avec ces autorisations.
 * @param x La valeur x du triplet.
 * @param y La valeur y du triplet.
 * @param z La valeur z du triplet.
 * @return un vecteur.
 */
extern Triplet *triplet_create_vector(double x, double y, double z);

/**
 * @brief Permet de générer un triplet de type Couleur avec ces autorisations.
 * @param x La valeur x du triplet.
 * @param y La valeur y du triplet.
 * @param z La valeur z du triplet.
 * @return une couleur.
 */
extern Triplet *triplet_create_color(double x, double y, double z);

/**
 * @brief Permet de générer un triplet de type Point avec ces autorisations non alloué dynamiquement.
 * @param x La valeur x du triplet.
 * @param y La valeur y du triplet.
 * @param z La valeur z du triplet.
 * @return un point.
 */
extern Triplet triplet_point(double x, double y, double z);

/**
 * @brief Permet de générer un triplet de type Vecteur avec ces autorisations non alloué dynamiquement.
 * @param x La valeur x du triplet.
 * @param y La valeur y du triplet.
 * @param z La valeur z du triplet.
 * @return un vecteur.
 */
extern Triplet triplet_vector(double x, double y, double z);

/**
 * @brief Permet de générer un triplet de type Couleur avec ces autorisations non alloué dynamiquement.
 * @param x La valeur x du triplet.
 * @param y La valeur y du triplet.
 * @param z La valeur z du triplet.
 * @return une couleur.
 */
extern Triplet triplet_color(double x, double y, double z);

/**
 * @brief Permet de générer un triplet de type Unknow avec ces autorisations.
 * @param x La valeur x du triplet.
 * @param y La valeur y du triplet.
 * @param z La valeur z du triplet.
 * @return un triplet.
 */
extern Triplet *triplet_create(double x, double y, double z);

/**
 * @brief Permet de faire l'operation de l'addition avec deux triplets.
 * @param current Le triplet sur lequel on va modifier les valeurs
 * @param subtracted Le triplet sur lequel on va récuperer les valeurs.
 * @return Si l'opération s'est bien effectué.
 */
extern bool triplet_add(Triplet *current, Triplet *subtracted);

/**
 * @brief Permet de faire l'operation de la soustraction avec deux triplets.
 * @param current Le triplet sur lequel on va modifier les valeurs
 * @param subtracted Le triplet sur lequel on va récuperer les valeurs.
 * @return Si l'opération s'est bien effectué.
 */
extern bool triplet_sub(Triplet *current, Triplet *subtracted);

/**
 * @brief Permet de faire l'operation de la multiplication avec un triplet et un scalaire.
 * @param current Le triplet sur lequel on va modifier les valeurs
 * @param scalar Le scalaire avec lequel on modifie les valeurs.
 * @return Si l'opération s'est bien effectué.
 */
extern bool triplet_mul(Triplet *current, double scalar);

/**
 * @brief Permet de faire l'operation du produit scalaire avec deux triplets.
 * @param current Le triplet sur lequel on va modifier les valeurs
 * @param multiplied Le triplet sur lequel on va récuperer les valeurs.
 * @return Le produit scalaire du triplet et du scalaire.
 */
extern double triplet_scalar_product(Triplet *current, Triplet *multiplied);

/**
 * @brief Permet de faire l'operation du produit vectoriel avec deux triplets.
 * @param current Le triplet sur lequel on va modifier les valeurs
 * @param multiplied Le triplet sur lequel on va récuperer les valeurs.
 * @return Si l'opération s'est bien effectué.
 */
extern bool triplet_vectorial_product(Triplet *current, Triplet *multiplied);

/**
 * @brief Permet de faire l'operation du produit de Schur avec deux triplets.
 * @param current Le triplet sur lequel on va modifier les valeurs
 * @param multiplied Le triplet sur lequel on va récuperer les valeurs.
 * @return Si l'opération s'est bien effectué.
 */
extern bool triplet_schur(Triplet *current, Triplet *mulitplied);

/**
 * @brief Permet de faire l'operation du calcul de la longeur avec le triplet.
 * @param current Le triplet sur lequel on va modifier les valeurs
 * @return La longueur du triplet.
 */
extern double triplet_length(Triplet *current);

/**
 * @brief Permet de faire l'operation du calcul de la normalisation avec le triplet.
 * @param current Le triplet sur lequel on va modifier les valeurs
 * @return Si l'opération s'est bien effectué.
 */
extern bool triplet_normalization(Triplet *current);

/**
 * @brief Permet de désallouer le triplet.
 * @param triplet Le triplet sur lequel on va désallouer.
 */
extern void triplet_destroy(Triplet *triplet);

/**
 * @brief Permet de d'afficher le triplet.
 * @param triplet Le triplet sur lequel on va afficher le contenu.
 */
extern void triplet_display(Triplet triplet);

#endif