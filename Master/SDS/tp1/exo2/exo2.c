#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Goal : Force the program to print "Authentication success"
*/

char username[64];
char password[64];
int is_authenticated = 0;

void auth_ok(void){
	puts("Authentication success!");
}
void auth_nok(void){
	puts("Authentication failed");
}

void check_login(char *u, char *p)
{
	// FIXME
}

int main(int argc, char **argv){
	if (argc != 3)
	{
		printf("Usage: %s <username> <password>\n", *argv);
		exit(1);
	}
	strcpy(username, argv[1]);
	strcpy(password, argv[2]);
	check_login(username, password);
	if (is_authenticated){
		auth_ok();
	}
	else{
		auth_nok();
	}
	return 0;
}
