#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "main.h"

class CKeyboard
{
    public:

    ALLEGRO_KEYBOARD_STATE klawiatura;

    void Get(ALLEGRO_KEYBOARD_STATE);
    bool Press(int);

};

class CMouse
{
    public:

    ALLEGRO_MOUSE_STATE mysz;
    bool click;

    void Get(ALLEGRO_MOUSE_STATE);
    bool Press(int);
    int getX() { return mysz.x; }
    int getY() { return mysz.y; }
    int getZ() { return mysz.z; }
    bool bound(int,int,int,int);
};


#endif // KEYBOARD_H_INCLUDED
