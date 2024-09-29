#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

bool check_right();

bool check_mdp(char *password, char *realpassword);

void find_mdp(char *user, char *password);