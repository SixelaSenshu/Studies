/**
 * @file Main.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief Programme qui permet de compiler et retourner le résultat du programme principale.
 * @date 1.01.2023
 * @version 1.0
 */
#ifndef _MAIN_H_
#define _MAIN_H_ 1
#include "triplets/Triplet.h"
#include "comparator/Compare.h"
#include "Raytrace/Raytrace.h"
#include "ReaderScene/ReaderScene.h"
#include "Tools/Character.h"
#include "Tools/Functions.h"
#include "Tools/Light.h"
#include "Tools/Tools.h"
#include "Tools/Triangle.h"

/**
 * @brief Fonction principal du programme.
 * @param argc Nombre d'arguments fournit dans la console.
 * @param argv Les arguments fournit dans la console (le tableau).
 * @return Un code d'erreur ou si le programme n'a rencontrer aucune erreur
 */
int main(int argc, char *argv[]);
#endif