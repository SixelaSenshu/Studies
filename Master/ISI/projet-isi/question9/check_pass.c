#include "check_pass.h"

bool check_right()
{
    int gid, egid;

    gid = getgid();   // real groupe id
    egid = getegid(); // effective group include

    printf("gid = %d, egid = %d\n", gid, egid);
    if (egid != gid)
    {
        printf("Vous ne faites pas partie du bon groupe pour l'utilisation de ce fichier\n");
        return false;
    }
    return true;
}

bool check_mdp(char *password, char *realpassword)
{
    if (strcmp(password, realpassword) == 0)
    {
        printf("Mot de passe correct\n");
        return true;
    }
    printf("Mot de passe incorrect\n");
    return false;
}

void find_mdp(char *user, char *password)
{
    FILE *fp;
    char line[128];   // buffer line
    char buffer[128]; // buffer token
    char sep[] = " "; // sepatartor
    char path[40] = "/home/administrateur/passwd/passwd.txt";
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Cannot open file %s\n", path);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("File %s opened\n", path);
        char *buffer;
        while (!feof(fp))
        {
            fgets(line, 128, fp);
            buffer = strtok(line, sep);
            if (strcmp(user, buffer) == 0)
            {
                buffer = strtok(NULL, " ");
                memset(password, 0, sizeof(password));
                strcpy(password, buffer);
                password[strlen(password) - 1] = '\0';
                return;
            }
        }

        strcpy(password, "NULL");
        fclose(fp);
    }
}

void delete_mdp(char *user, char *newpasswd)
{
    FILE *fp;
    char line[128];   // buffer line
    char buffer[128]; // buffer token
    char sep[] = " "; // sepatartor
    char path[40] = "/home/administrateur/passwd/passorwd.txt";
    fp = fopen(path, "r");
    if (fp == NULL)
    {
        printf("Cannot open file %s\n", path);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("File %s opened\n", path);
        char *buffer;
        while (!feof(fp))
        {
            fgets(line, 128, fp);
            buffer = strtok(line, sep);
            if (strcmp(user, buffer) == 0)
            {
                fwrite(line, sizeof(char), strlen(line), fp);
            }
        }
        fclose(fp);
    }
}

void add_mdp(char *user, char *newpasswd)
{
    cryptPassword(newpasswd);
    FILE *fp;
    char line[128]; // buffer line
    char sep[] = " ";
    char buffer[128]; // buffer token  // sepatartor
    char path[40] = "/home/administrateur/passwd/password.txt";
    fp = fopen(path, "a");
    if (fp == NULL)
    {
        printf("Cannot open file %s\n", path);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("File %s opened\n", path);
        char *buffer;
        while (!feof(fp))
        {
            fgets(line, 128, fp);
            buffer = strtok(line, sep);
        }
        fwrite(user, sizeof(char), strlen(user), fp);
        fclose(fp);
    }
}