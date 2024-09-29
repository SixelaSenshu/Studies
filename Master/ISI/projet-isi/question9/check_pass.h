#ifndef _CHECK_PASSWD_
#define _CHECK_PASSWD_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include "cryptage.h"

bool check_right();

bool check_mdp(char *password, char *realpassword);

void find_mdp(char *user, char *password);

void delete_mdp(char *user, char *newpasswd);

void add_mdp(char *user, char *newpasswd);

#endif // !_CHECK_PASSWD_