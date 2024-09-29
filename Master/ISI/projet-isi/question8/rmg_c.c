#include "check_pass.h"

int main(int argc, char *argv[])
{
    int gid, egid;

    if (argc < 2)
    {
        printf("Missing argument\n");
        exit(EXIT_FAILURE);
    }

    if (!check_right())
    {
        exit(EXIT_FAILURE);
    }

    char *user = malloc(sizeof(char) * 30);
    user = getlogin();
    char *input = malloc(sizeof(char) * 30);
    printf("Entrez le mot de passe (30 max): ");
    scanf("%s", input);
    FILE *fp;
    printf("Recherche du mot de passe...\n");
    char *buffer = malloc(sizeof(char) * 30);
    find_mdp(user, buffer);
    if (check_mdp(input, buffer))
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            printf("Ne peux ouvrir le fichier %s\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        printf("Fichier %s ouvert\n", argv[1]);
        fclose(fp);
        exit(EXIT_SUCCESS);
    }
    else
    {
        exit(EXIT_FAILURE);
    }
    return 0;
}