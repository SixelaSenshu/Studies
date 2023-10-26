#include "../../headers/Raytrace/MainRaytrace.h"

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
        return EXIT_FAILURE;
    ReaderScene *scene = readerscene_create(argv[1]);
    if (!scene)
    {
        goto error;
    }
    if (!readerscene_readtext(scene))
    {
        printf("nop");
        goto error;
    }
    if (!raytrace_create_image(scene))
        goto error;
    readerscene_destroy(scene);
    return EXIT_SUCCESS;

error:
    if (scene)
        readerscene_destroy(scene);
    return EXIT_FAILURE;
}
