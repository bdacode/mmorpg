#include "bitmap.h"

//template <typename T>
//ALLEGRO_BITMAP* loadBmp(T path)
ALLEGRO_BITMAP* loadBmp(char* path)
{
    ALLEGRO_BITMAP* bmp = al_load_bitmap(path);
    if(!bmp)
    {
        string error = "ERROR: Cannot load bitmap '";
        error += path;
        error += "'";
        logger << error;
        bmp = al_load_bitmap("media/error.png");
    }

    return bmp;
}

int getBmpW(ALLEGRO_BITMAP* bmp)
{
    return al_get_bitmap_width(bmp);
}

int getBmpH(ALLEGRO_BITMAP* bmp)
{
    return al_get_bitmap_height(bmp);
}
