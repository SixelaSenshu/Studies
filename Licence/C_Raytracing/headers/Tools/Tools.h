/**
 * @file Tools.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief Programme qui permet de manipuler et créer les objects de scènes.
 * @date 1.01.2023
 * @version 1.0
 */
#ifndef _TOOLS_H_
#define _TOOLS_H_ 1

#include "../triplets/Triplet.h"
/**
 * @brief Structure qui initialise une caméra (les informations pour la créer)
 *
 */
typedef struct camera
{
    Triplet lookFrom; //!< La position de l'oeil.
    Triplet lookAt;   //!< Le point visé par l'oeil.
    Triplet up;       //!< La direction vers le haut de l'oeil.
    double degree;    //!< L'angle de vue.
} Camera;

/**
 * @brief Structure qui initialise les couleurs (les informations pour la créer)
 *
 */
typedef struct color
{
    Triplet *ambiant;       //!< La couleur ambiante.
    Triplet *diffuse;       //!< La couleur de l'obje.
    Triplet *specular;      //!< La lumière réfléchie
    unsigned int shininess; //!< Intensité.

} Color;

/**
 * @brief Enumére les differents types de couleurs.
 *
 */
typedef enum typeLight
{
    LIGHT_DIRECTIONAL, //!< La lumière global
    LIGHT_POINT        //!< Source de lumière
} TypeLight;

/**
 * @brief Structure qui initialise une lumière (les informations pour la créer)
 *
 */
typedef struct light
{
    TypeLight type;    //!< Le type de lumière.
    Triplet point;     //!< Le point si c'est une source.
    Triplet direction; //!< La direction si c'est une lumière globale.
    Triplet color;     //!< La couleur de la lumière.
} Light;

/**
 * @brief Structure qui initialise une sphère (les informations pour la créer)
 *
 */
typedef struct sphere
{
    Triplet center; //!< Le centre de la sphère.
    double radius;  //!< Le rayon.
    Triplet color;  //!< La couleur de la sphère.

} Sphere;

/**
 * @brief Structure qui initialise un triangle (les informations pour la créer)
 *
 */
typedef struct triangle
{
    Triplet point1; //!< Le point 1 du triangle.
    Triplet point2; //!< Le point 2 du triangle.
    Triplet point3; //!< Le point 3 du triangle.
    Triplet color;  //!< La couleur du triangle.
} Triangle;

/**
 * @brief Structure qui initialise un plan (les informations pour la créer)
 *
 */
typedef struct plane
{
    Triplet point;  //!< Le point de repère.
    Triplet vector; //!< La direction du plan.
} Plane;

/**
 * @brief Alloue une instance de Camera
 *
 * @param lookFrom La positon de l'oeil.
 * @param lookAt Le point ou regarde l'oeil.
 * @param up La direction vers le haut de l'oeil.
 * @param degree L'angle de vue
 * @return Une instance ou NULL.
 */
extern Camera *tools_create_camera(Triplet lookFrom, Triplet lookAt, Triplet up, double degree);

/**
 * @brief  Désalloue une instance de Camera.
 *
 * @param camera L'instance qui sera désalloué.
 */
extern void tools_destroy_camera(Camera *camera);

/**
 * @brief Alloue une instance de Color.
 *
 * @param ambiant La couleur ambiante.
 * @param diffuse La couleur de l'objet.
 * @param specular La lumière réflichissante.
 * @param shininess L'intensité.
 * @return Une instance ou NULL.
 */
extern Color *tools_create_color(Triplet ambiant, Triplet diffuse, Triplet specular, int shininess);

/**
 * @brief Désalloue une instance de Color.
 *
 * @param color L'instance qui sera désalloué.
 */
extern void tools_destroy_color(Color *color);

/**
 * @brief Alloue une instance de Light.
 *
 * @param type Le type de lumière.
 * @param point La source. (si sa n'est pas une lumière globale)
 * @param direction La direction (si sa n'est pas une source)
 * @param color La couleur de la lumière.
 * @return Une instance ou NULL.
 */
extern Light *tools_create_light(TypeLight type, Triplet point, Triplet direction, Triplet color);

/**
 * @brief  Désalloue une instance de Light.
 *
 * @param light L'instance qui sera désalloué.
 */
extern void tools_destroy_light(Light *light);

/**
 * @brief Alloue une instance de Sphere.
 *
 * @param center Le centre de la sphère ( le point ).
 * @param radius Le rayon de la sphère.
 * @param color La couleur de la sphère.
 * @return Une instance ou NULL.
 */
extern Sphere *tools_create_sphere(Triplet center, double radius, Triplet color);

/**
 * @brief Désalloue une instance de Sphere.
 *
 * @param sphere L'instance qui sera désalloué.
 */
extern void tools_destroy_sphere(Sphere *sphere);

/**
 * @brief Alloue une instance de Triangle.
 *
 * @param point1 Le point 1 du triangle.
 * @param point2 Le point 2 du triangle.
 * @param point3 Le point 3 du triangle.
 * @param color La couleur du triangle.
 * @return Une instance ou NULL.
 */
extern Triangle *tools_create_triangle(Triplet point1, Triplet point2, Triplet point3, Triplet color);

/**
 * @brief Désalloue une instance de Triangle.
 *
 * @param triangle L'instance qui sera désalloué.
 */
extern void tools_destroy_triangle(Triangle *triangle);

/**
 * @brief Alloue une instance de Plane.
 *
 * @param point Le point de repère.
 * @param vector La direction du plan.
 * @return Une instance ou NULL.
 */
extern Plane *tools_create_plane(Triplet point, Triplet vector);

/**
 * @brief Désalloue une instance de Plane.
 *
 * @param plane L'instance qui sera désalloué.
 */
extern void tools_destroy_plane(Plane *plane);

/**
 * @brief Affiche le contenu de la Camera.
 *
 * @param camera L'instance qui sera afficher.
 */
extern void tools_to_string_camera(Camera *camera);

/**
 * @brief Affiche le contenu de la couleur.
 *
 * @param color L'instance qui sera afficher.
 */
extern void tools_to_string_color(Color *color);

/**
 * @brief Affiche le contenu de la lumière.
 *
 * @param light L'instance qui sera afficher.
 */
extern void tools_to_string_light(Light *light);

/**
 * @brief Affiche le contenu de la Sphere.
 *
 * @param sphere L'instance qui sera afficher.
 */
extern void tools_to_string_sphere(Sphere *sphere);

/**
 * @brief Affiche le contenu du triangle.
 *
 * @param triangle L'instance qui sera afficher.
 */
extern void tools_to_string_triangle(Triangle *triangle);

/**
 * @brief Affiche le contenu du plan.
 *
 * @param plane L'instance qui sera afficher.
 */
extern void tools_to_string_plane(Plane *plane);

#endif