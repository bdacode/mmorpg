#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include "main.h"
#include "bitmap.h"
#include "input.h"

extern CKeyboard key;
extern CMouse mouse;

class cButton{
    public:
        cButton(int, int, string);

        inline bool get_click(){return click;}

        void update();
        void draw();
    private:
        int x, y;
        int w, h;
        bool click;
        string name;

        bool orWait; int waiting;
        bool pressed;

        ALLEGRO_FONT* font_button;
};

class cBool{
    public:
        cBool(int, int);
    private:
        int x, y;
        int w, h;
        bool click;
};

#endif // GUI_HPP_INCLUDED
