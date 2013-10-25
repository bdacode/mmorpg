#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "main.h"
#include "bitmap.h"
#include "input.h"
#include "tile.h"

class CMap {
    int w, h;
    CTile** map;

    public:
    CMap();
    CMap(int,int);
    ~CMap();

    inline int getWidth() { return w; }
    inline int getHeight() { return h; }
    inline int getTileID(int x, int y) { return map[x][y].getID(); }
    inline void setTileID(int x, int y, int id) { return map[x][y].setID(id); }

    void resize(int, int);
    void createMap(ENetPacket*);
    void getMapFromString(string);
    void load();
    void render(CCamera*);
};


#endif // MAP_H_INCLUDED
