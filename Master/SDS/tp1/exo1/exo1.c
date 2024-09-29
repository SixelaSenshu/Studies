#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Goal : force the program to execute a shell
*/

int main(int argc, char **argv){
	char cmd[256];
	if (argc != 2)
	{
		printf("Usage: %s <username>\n", argv[0]);
		return 1;
	}
	snprintf(cmd, sizeof(cmd), "echo 'hello %s'", argv[1]);
	system(cmd);
	return 0;
}
