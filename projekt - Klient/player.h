#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "main.h"
#include "input.h"
#include "client.h"

struct SPos {
    int x, y;
};

class CPlayer {

public:
    CPlayer();
    ~CPlayer();

    SPos newPos;
    SPos oldPos;

    int timeToSend;

    //czesci ciala (same ID tylko potrzebne. Obrazek ladowany przy tworzeniu bohatera etc.)
    int hair, head, body, leg, boots;

    void update(CKeyboard);
    void render();
};


#endif // PLAYER_H_INCLUDED
