#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Goal : Force the program to print "Authentication success!"
*/

void auth_ok(void){
	puts("Authentication success!");
}
void auth_nok(void){
	puts("Authentication failed");
}

int check_login(char *u, char *p)
{
	// FIXME
	return 0;
}

int doit(char *u, char *p)
{
	char username[64];
	char password[64];
	strcpy(username, u);
	strcpy(password, p);
	if(check_login(username, password))
	{
		auth_ok();
	}
	else
	{
		auth_nok();
	}
	return 0;
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		printf("Usage: %s <username> <password>\n", *argv);
		return 0;
	}
	doit(argv[1], argv[2]);
	return 0;
}
