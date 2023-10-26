
/**
 * @file Compare.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief outils permettant de creer un compateur qui permet de comparer deux images et de créer la différence.
 * @date 1.01.2023
 * @version 1.0
 */
#ifndef _COMPARE_H_
#define _COMPARE_H_

#include <stdbool.h>
#include <string.h>
#include "../../lib/FreeImage/Source/FreeImage.h"
#include "../triplets/Triplet.h"

/**
 * @brief Une instance avec les informations d'un pixel.
 *
 */
typedef struct _pixel
{
    int r, //<! La composante rouge
        g, //<! La composante verte
        b; //<! La composante bleu
} Pixel;

/**
 * @brief Une instance avec les informations de l'image.
 *
 */
typedef struct _image
{
    FIBITMAP *btm; //<! Le pointeur de l'image.
    int width,     //<! La taille de l'image.
        height;    //!< La hauteur de l'image.
} Image;

/**
 * @brief Permet de générer une image à partir de son chemin.
 *
 * @param filename Le chemin de l'image.
 * @return Une nouvelle instance Image alloué
 */
extern Image *image_create_with_path(char *filename);

/**
 * @brief Détruit l'instance Image.
 *
 * @param img L'instance qui sera détruit.
 */
extern void image_destroy(Image *img);

/**
 * @brief Permet d'afficher les information sur une image.
 *
 * @param img Image
 */
extern void image_display(Image *img);

/**
 * @brief Permet de comparer deux images et donner les différences
 *
 * @param img1 La premieère Image.
 * @param img2 La deuxième Image.
 * @return Le nombre de pixel différents
 */
extern int image_compare(Image *img1, Image *img2);

/**
 * @brief Compare deux images et en créer une image avec les différences
 *
 * @param filename1 Le premier chemin de l'image.
 * @param filename2 Le deuxième chemin de l'image.
 * @return Le nombre de pixel différents.
 */
extern int image_compare_between(char *filename1, char *filename2);

#endif
