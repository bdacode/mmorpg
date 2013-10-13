#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "CMain.h"
#include "bitmap.h"

extern const int WIN_W, WIN_H, WIN_FPS;
extern string WIN_NAME;

extern ALLEGRO_FONT* font;

// budowanie stuff'u
extern int activeID, wysunieteMenu;
extern string opisID[];
extern bool mouseClick, pause;
extern bool mouse2click;

#endif // MAIN_H_INCLUDED
