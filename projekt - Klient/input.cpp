#include "input.h"

void CKeyboard::Get(ALLEGRO_KEYBOARD_STATE klaw)
{
    klawiatura = klaw;
}

bool CKeyboard::Press(int key)
{
    if(al_key_down(&klawiatura, key))
        return true;

    return false;
}


void CMouse::Get(ALLEGRO_MOUSE_STATE mouse)
{
    mysz = mouse;
}

bool CMouse::Press(int key)
{
    if(mysz.buttons == key)
        return true;

    return false;
}
