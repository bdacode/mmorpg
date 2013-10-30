#ifndef GUI_HPP_INCLUDED
#define GUI_HPP_INCLUDED

#include "main.h"
#include "bitmap.h"
#include "input.h"

extern CKeyboard key;
extern CMouse mouse;

enum GUI_DYNAMICS { GUI_STATIC, GUI_MOVE };
/***button***/
class cButton{
    public:
        cButton(int, int, int, int, string, GUI_DYNAMICS);
        cButton(int, int, int, int, string, string, GUI_DYNAMICS);

        inline bool get_click(){return click;}
        inline void hide(bool){this->life=life;}

        void render();
    private:
        int x, y;
        int w, h;
        int wStatic, hStatic;
        int centerX, centerY;
        int distanceX, distanceY;
        int mouseOldX, mouseOldY;
        bool click, pressed, life, modified;
        string name, path;

        bool orWait; int waiting;

        GUI_DYNAMICS dynamics;
        ALLEGRO_BITMAP* background;
        ALLEGRO_FONT* font_button;
};

/***message box***/
class cMessageBox{
    public:
        cMessageBox(int, int, int, int, string, string, GUI_DYNAMICS);

        void setText(string);
        void render();

    private:
        int x, y;
        int w, h;
        int wStatic, hStatic;
        int centerX, centerY;
        int distanceX, distanceY;
        int mouseOldX, mouseOldY;
        bool life, pressed, modified;
        string text, path;

        GUI_DYNAMICS dynamics;
        ALLEGRO_BITMAP* background;
        ALLEGRO_FONT* font_button;
};

/***text box***/
class cTextBox{

};

#endif // GUI_HPP_INCLUDED
