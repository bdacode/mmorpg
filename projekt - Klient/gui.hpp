#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include "main.h"
#include "bitmap.h"
#include "input.h"

extern CKeyboard key;
extern CMouse mouse;

/***button***/
class cButton{
    public:
        cButton(int, int, int, int, string);
        cButton(int, int, int, int, string, string);

        inline bool get_click(){return click;}

        void update();
        void draw();
    private:
        int x, y;
        int centerX, centerY;
        int w, h;
        bool click;
        string name;

        bool orWait; int waiting;
        bool pressed;
        string path;

        ALLEGRO_BITMAP* background;
        ALLEGRO_FONT* font_button;
};

/***message box***/

#endif // GUI_HPP_INCLUDED
