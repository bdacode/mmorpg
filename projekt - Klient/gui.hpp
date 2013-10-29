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

        void render();
    private:
        int x, y;
        int w, h;
        int centerX, centerY;
        bool click;
        string name;

        bool orWait; int waiting;
        bool pressed;
        string path;

        ALLEGRO_BITMAP* background;
        ALLEGRO_FONT* font_button;
};

/***message box***/
enum GUI_DYNAMICS { GUI_STATIC, GUI_MOVE };
class cMessageBox{
    public:
        cMessageBox(int, int, int, int, string, string, GUI_DYNAMICS);

        void setText(string);
        void render();
        GUI_DYNAMICS dynamics;

    private:
        int x, y;
        int w, h;
        int wHelp, hHelp;
        int centerX, centerY;
        int distanceX, distanceY;
        int mouseOldX, mouseOldY;
        bool life, pressed, modified;
        string text, path;
        ALLEGRO_BITMAP* background;
        ALLEGRO_FONT* font_button;
};

#endif // GUI_HPP_INCLUDED
