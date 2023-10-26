/**
 * @file ReaderScene.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief Programme qui permet de parser un fichier et créer les objets de scène.
 * @date 1.01.2023
 * @version 1.0
 */
#ifndef _READERSCENE_H_
#define _READERSCENE_H_ 1

#include "../Tools/Character.h"
#include "../Tools/Tools.h"

/**
 * @brief Lecteur de fichier permettant d'instancier avec les informations une image.
 * Contient tous les informations pour constituer une image en 2D ou 3D.
 * @warning Il y a certaines conditions importantes : SizeTriangles doit être instancier pour pouvoir créer des triangles.
 * Toutes erreurs dans le fichier peut causer l'arret de la lecture, créer un objet par défaut ou être ignorer.
 */
typedef struct readerScene
{
    int height;           //!< La hauteur de l'image
    int width;            //!< La longeur de l'image
    int nbPixels;         //!< Le nombre de pixels de l'image.
    int nbPoints;         //!< Le nombre de points.
    int nbTriangles;      //!< Le nombre de triangles.
    int nbSpheres;        //!< Le nombre de sphères.
    int nbLights;         //!< Le nombre de lumières.
    int nbPlanes;         //!< Le nombre de plans
    int nbObjs;           //!< Le nombre d'objets créés.
    int sizePoints;       //!< La taille alloué pour la liste des points.
    int sizeTriangles;    //!< La taille alloué pour la liste des triangles.
    int sizeSpheres;      //!< La taille alloué pour la liste des spheres.
    int sizeLights;       //!< La taille alloué pour la liste des lumières
    int sizePlanes;       //!< La taille alloué pour la liste des plans
    bool hasdiffuse;      //!< Si la couleur sera l'ambiante ou non
    char *filename;       //!< Le nom de l'image qui sera généré.
    bool shadow;          // Si il y a des ombres.
    Camera *camera;       //!< La caméra qui sera modélisé dans les images.
    Color *couleurs;      //!< Les couleurs qui seront modélisé dans les images
    Light **lights;       //!< Les lumières qui seront modélisé dans les images.
    Triplet **points;     //!< Les points qui seront utilisé par les vecteurs dans les images.
    Sphere **spheres;     //!< Les spheres qui seront modélisé dans les images.
    Triangle **triangles; //!< Les triangles qui seront modélisé dans les images.
    Plane **planes;       //!< Le plan qui sera utilisé pour les images.
    FILE *file;           //!< Fichier qui est lu par le lecteur.
} ReaderScene;

/**
 * @brief Permet d'allouer un lecteur de scène et de l'ouvrir.
 *
 * @param filename Le chemin du fichier.
 * @return L'instance ReaderScene ou NULL?
 */
extern ReaderScene *readerscene_create(char *filename);

/**
 * @brief Permet d'ouvrir un fichier d'un lecteur.
 *
 * @param scene L'instance ReaderScene.
 * @param filename Le chemin du fichier.
 * @return true
 * @return false
 */
extern bool readerscene_openfile(ReaderScene *scene, char *filename);

/**
 * @brief Permet de fermer un fichier d'un lecteur.
 *
 * @param scene L'instance ReaderScene.
 * @return true
 * @return false
 */
extern bool readerscene_quitfile(ReaderScene *scene);

/**
 * @brief Permet de lire et appliquer les fonctions pour une ligne du fichier.
 *
 * @param scene L'instance ReaderScene.
 * @param object L'objet qui doit être lu
 * @return int
 */
extern int readerscene_apply(ReaderScene *scene, char *object);

/**
 * @brief Permet de lire un fichier ouvert.
 *
 * @param scene L'instance ReaderScene.
 * @return true
 * @return false
 */
extern bool readerscene_readtext(ReaderScene *scene);

/**
 * @brief Permet de lire un ligne dans le fichier ouvert
 *
 * @param scene L'instance ReaderScene.
 * @return int
 */
extern int readerscene_readline(ReaderScene *scene);

/**
 * @brief Désallou le lecteur de scene.
 *
 * @param scene L'instance ReaderScene.
 */
extern void readerscene_destroy(ReaderScene *scene);

/**
 * @brief Affiche dans la console tous les informations sur le lecteur.
 *
 * @param scene L'instance ReaderScene.
 * @param choice Le choix d'affichage.
 */
extern void readerscene_tostring(ReaderScene *scene, int choice);

#endif