#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

struct SPos {
    int x, y;
};

class CPlayer {

public:
    CPlayer();
    ~CPlayer();

    SPos pos;

    //czesci ciala (same ID tylko potrzebne. Obrazek ladowany przy tworzeniu bohatera etc.)
    int hair, head, body, leg, boots;

    void render();
};


#endif // PLAYER_H_INCLUDED
