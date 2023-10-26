/**
 * @file Character.h
 * @author Alexis Bernard & Antoine Wybo
 * @brief Programme qui permet de manipuler des chaînes de caractères un par un.
 * @date 1.01.2023
 * @version 1.0
 */
#ifndef _CHARACTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/// @brief Compare deux mots selon leurs lettres et leur taille
/// @param word1 Mot qui sera comparer
/// @param word2 Mot avec lequelle on compare
/// @return Si le premier mot est plus grand ou plus petit
int compare(char *word1, char *word2);

/// @brief Calcule la taille d'un mot
/// @param word Mot dont on calcule la taille
/// @return La taille du mot
unsigned int size_word(char *word);

/// @brief Indique si le caractère est une lettre Minuscule
/// @param c Caractère en cours de vérification
/// @return si la vérification est un succès
int is_small_letter(char c);

/// @brief Indique si le caractère est une lettre Majuscule
/// @param c Caractère en cours de vérification
/// @return si la vérification est un succès
int is_tall_letter(char c);

/// @brief Indique si le caractère est un nombre
/// @param c Caractère en cours de vérification
/// @return si la vérification est un succès
int is_number(char c);

/// @brief Indique si le caractère est une lettre ou non
/// @param c Caractère en cours de vérification
/// @return si la vérification est un succès
int is_specific_character(char c);

/// @brief Convertie un caractère majuscule en miniscule
/// @param c Caractère en cours de transformation
/// @return si la convertion est un succès
char convert_tall_to_small_character(char c);

#define _CHARACTER_H 1
#endif
