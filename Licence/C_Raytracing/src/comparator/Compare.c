#include "../../headers/comparator/Compare.h"

static FIBITMAP *image_load_image(FIBITMAP *btm, char *filename);

extern Image *image_create_with_path(char *filename)
{
    if (!filename)
        return NULL;
    FIBITMAP *btm = NULL;
    Image *img = (Image *)malloc(sizeof(Image));
    if (!img)
    {
        fprintf(stderr, "[ALLOCATION] Problème d'allocation.\n");
        goto quit;
    }
    btm = image_load_image(btm, filename);
    if (!btm)
        goto quit;

    img->btm = btm;
    img->width = FreeImage_GetWidth(img->btm);
    img->height = FreeImage_GetHeight(img->btm);
    return img;
quit:
    if (btm != NULL)
        free(btm);
    if (img != NULL)
        free(img);
    return NULL;
}

static FIBITMAP *image_load_image(FIBITMAP *btm, char *filename)
{
    btm = FreeImage_Load(FIF_PNG, filename, PNG_IGNOREGAMMA);
    if (!btm)
    {
        fprintf(stderr, "[LOAD] Problème de chargement d'image\n");
        return NULL;
    }

    return btm;
}

extern void image_destroy(Image *img)
{
    if (img)
    {
        if (img->btm != NULL)
            FreeImage_Unload(img->btm);
        free(img);
    }
}

extern int image_compare(Image *img1, Image *img2)
{

    FIBITMAP *diff_image = FreeImage_Allocate(img1->width, img1->height, FreeImage_GetBPP(img1->btm), 0, 0, 0);

    Pixel pixelsImg1[img1->width][img1->height], pixelsImg2[img2->width][img2->height];
    int i, j;
    int nbDifferences = 0;
    RGBQUAD color, color2, diff_color;

    if ((img1->width != img2->width) || (img1->height != img2->height))
        return -1;
    for (i = 0; i < img1->width; i++)
    {
        for (j = 0; j < img1->height; j++)
        {
            FreeImage_GetPixelColor(img1->btm, i, j, &color);
            FreeImage_GetPixelColor(img2->btm, i, j, &color2);

            pixelsImg1[i][j] = (Pixel){color.rgbRed, color.rgbGreen, color.rgbBlue};
            pixelsImg2[i][j] = (Pixel){color2.rgbRed, color2.rgbGreen, color2.rgbBlue};

            diff_color.rgbRed = abs(color.rgbRed - color2.rgbRed);
            diff_color.rgbGreen = abs(color.rgbGreen - color2.rgbGreen);
            diff_color.rgbBlue = abs(color.rgbBlue - color2.rgbBlue);

            FreeImage_SetPixelColor(diff_image, i, j, &diff_color);
        }
    }

    char *diff_filename = "./diff.png";
    FreeImage_Save(FIF_PNG, diff_image, diff_filename, 0);
    FreeImage_Unload(diff_image);

    for (i = 0; i < img1->width; i++)
    {
        for (j = 0; j < img1->height; j++)
        {
            if (!(pixelsImg1[i][j].r == pixelsImg2[i][j].r && pixelsImg1[i][j].g == pixelsImg2[i][j].g && pixelsImg1[i][j].b == pixelsImg2[i][j].b))
                nbDifferences++;
        }
    }
    return nbDifferences;
}

extern void image_display(Image *img)
{
    fprintf(stdin, "Witdh : %d |Height : %d \n", img->width, img->height);
}

extern int image_compare_between(char *filename1, char *filename2)
{
    int res = false;
    Image *img1 = NULL, *img2 = NULL;

    if (!strcmp(filename1, filename2))
        return 0;
    img1 = image_create_with_path(filename1);
    if (!img1)
    {
        fprintf(stderr, "[ALLOCATION] Problème d'allocation.\n");
        goto quit;
    }
    img2 = image_create_with_path(filename2);
    if (!img2)
    {
        fprintf(stderr, "[ALLOCATION] Problème d'allocation.\n");
        goto quit;
    }
    res = image_compare(img1, img2);

    if (img1)
        image_destroy(img1);
    if (img2)
        image_destroy(img2);
    return res;
quit:
    if (img1)
        image_destroy(img1);
    if (img2)
        image_destroy(img2);
    return -1;
}
