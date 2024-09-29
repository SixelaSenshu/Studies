#include "rmg_c.h"
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Missing argument\n");
        exit(EXIT_FAILURE);
    }

    char *user = malloc(sizeof(char) * 30);
    user = getlogin();
    char *buffer = malloc(sizeof(char) * 30);
    find_mdp(user, buffer);
    if (strcmp(buffer, "END") == 0)
    {
        // up
        exit(EXIT_SUCCESS);
    }
    else
    {
        char *input = malloc(sizeof(char) * 30);
        printf("Entrez votre ancien mot de passe (30 max):");
        scanf("%s", input);
        cryptPassword(input);
        if (check_mdp(input, buffer))
        {
            printf("Mot de passe mis à jour\n");
            delete_mdp(user, argv[1]);
            cryptPassword(argv[1]);
            add_mdp(user, argv[1]);
            exit(EXIT_SUCCESS);
        }
        else
        {
            printf("Wrong password\n");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}