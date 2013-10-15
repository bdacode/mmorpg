#ifndef TILE_H_INCLUDED
#define TILE_H_INCLUDED

class CTile
{
    int x,y, ID;
    bool isCollide;

public:
    CTile();

    inline int getX() { return x; }
    inline int getY() { return y; }
    inline int getID() { return ID; }
};



#endif // TILE_H_INCLUDED
