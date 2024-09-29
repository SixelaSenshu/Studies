#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{      
    int gid,uid,egid,euid;
    gid = getgid(); // real groupe id
    uid = getuid(); // read user id
    egid = getegid(); // effective group id
    euid = geteuid(); // effective user id

    printf("gid = %d, uid = %d, egid = %d, euid = %d\n", gid, uid, egid, euid);

    FILE *fp;
    if(argc < 2){
        printf("Missing argument\n");
        exit(EXIT_FAILURE);
    }
    printf("Hello, world\n");
    fp = fopen(argv[1], "r");
    if(fp == NULL){
        printf("Cannot open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    printf("File %s opened\n", argv[1]);
    fclose(fp);
    exit(EXIT_SUCCESS);
    return 0;
}
