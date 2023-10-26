#include "../../headers/Tools/Character.h"

///////////////////////  Fonctions  //////////////////////////////////////////

int compare(char *word1, char *word2)
{
    int i = 0;
    if (strcmp(word1, word2) == 0)
        return 2; // Si il est égale
    while (word1[i] != '\n' && word2[i] != '\n')
    {
        if (word1[i] > word2[i])
            return 1;
        else if (word1[i] < word2[i])
            return 0;
        i++;
    }
    if (word1[i] == '\0')
        return 0;
    return 1;
}

unsigned int size_word(char *word)
{
    assert(word);
    unsigned int ind = 0;
    char letter = word[0];
    while (letter != '\0')
    {
        letter = word[++ind];
    }
    return ind;
}

int is_small_letter(char c)
{
    if (c >= 'a' && c <= 'z')
    {
        return 1;
    }
    return 0;
}

int is_tall_letter(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        return 1;
    }
    return 0;
}

int is_number(char c)
{
    if (c >= '0' && c <= '9')
    {
        return 1;
    }
    return 0;
}
int is_specific_character(char c)
{
    if (is_tall_letter(c))
        return 0;
    if (is_small_letter(c))
        return 0;
    if (is_number(c))
        return 0;
    else
        return 1;
}

char convert_tall_to_small_character(char c)
{
    if (c >= 'A' && c <= 'Z')
    {
        int res = c + 32;
        return res;
    }
    else
    {
        return c;
    }
}
