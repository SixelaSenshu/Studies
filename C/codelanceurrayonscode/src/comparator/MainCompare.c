
#include "../../headers/comparator/MainCompare.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "[USAGE] Nombre de paramètres incorrect : ./compare filename filename \n");
        return EXIT_FAILURE;
    }
    FreeImage_Initialise(TRUE);

    int res = image_compare_between(argv[1], argv[2]);

    FreeImage_DeInitialise();
    if (res == -1 || res > 1000)
    {
        fprintf(stdout, "KO\n%d\n", res);
        return EXIT_FAILURE;
    }
    fprintf(stdout, "OK\n%d\n", res);
    return EXIT_SUCCESS;
}
