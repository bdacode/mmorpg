#ifndef BITMAP_H_INCLUDED
#define BITMAP_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

#include <vector>
#include <cstdio>

#include <iostream>
#include <time.h>
#include <math.h>
#include <fstream>

#include "logger.h"

using namespace std;

ALLEGRO_BITMAP* loadBmp(char* path);

int getBmpW(ALLEGRO_BITMAP* bmp);
int getBmpH(ALLEGRO_BITMAP* bmp);


#endif // BITMAP_H_INCLUDED
