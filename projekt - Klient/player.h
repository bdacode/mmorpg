#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "main.h"
#include "input.h"
#include "client.h"

struct SPos {
    int x, y;
};

extern ALLEGRO_BITMAP* IMG_player;

class CPlayer {

public:
    CPlayer();
    ~CPlayer();

    SPos newPos;
    SPos oldPos;

    string nick;

    int timeToSend;

    //czesci ciala (same ID tylko potrzebne. Obrazek ladowany przy tworzeniu bohatera etc.)
    int hair, head, body, leg, boots;

    void update(CKeyboard);
    void render();
};

void player_updatePos(void*);

class COtherPlayer {
public:
    SPos pos;
    string nick;

    COtherPlayer(string n)
        : nick(n)
    {
        pos.x = pos.y = 0;
    }
};

extern vector <COtherPlayer> v_otherPlayers;


#endif // PLAYER_H_INCLUDED
