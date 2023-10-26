#include "../../headers/ReaderScene/MainReaderScene.h"

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
        return EXIT_FAILURE;
    ReaderScene *scene = readerscene_create(argv[1]);
    if (!scene)
    {
        return EXIT_FAILURE;
    }

    if (!readerscene_readtext(scene))
    {
        readerscene_tostring(scene, 0);
        readerscene_destroy(scene);
        return EXIT_FAILURE;
    }
    readerscene_tostring(scene, 1);
    readerscene_destroy(scene);
    return EXIT_SUCCESS;
}
