#include "map.h"

int SIZE_TILE_W = 50,
    SIZE_TILE_H = 50;

CMap::CMap() {
    w = h = 10;
}

CMap::CMap(int w, int h)
    : w(w), h(h) {
    map = new CTile*[w];
    for(int i = 0; i < w; ++i)
        map[i] = new CTile[h];

    // DEBUG
    //for(int x = 0; x < w; ++x)
    //    for(int y = 0; y < h; ++y)
    //        map[x][y].setID(0);
}

CMap::~CMap() {
    for(int i = 0; i < w; i++)
        delete[] map[i];

    delete[] map;
}

void CMap::getMapFromString(string file)
{
    string tile = "";
    int index = 0, x = 0, y = 0;
    for(int i = 0; i < file.size(); ++i)
        if(file[i] != ' ') {
            tile.resize(tile.size()+1);
            tile[index] = file[i];
            ++index;
        }
        else {
            map[x][y].setID(atoi(tile.c_str()));
            ++x;
            if(x >= w) {
                x = 0;
                ++y;
            }
            index = 0;
        }
}

ALLEGRO_BITMAP* TILE_terrain[2];

void CMap::load() {
    TILE_terrain[0] = loadBmp("media/map/grass.png");
    TILE_terrain[1] = loadBmp("media/map/dirt.png");
}

void CMap::render() {
    for(int x = 0; x < w; ++x)
        for(int y = 0; y < h; ++y) {
            if(map[x][y].getID() == 0)
                al_draw_scaled_bitmap(TILE_terrain[0], 0,0, getBmpW(TILE_terrain[0]),getBmpW(TILE_terrain[0]),
                                      x*SIZE_TILE_W,y*SIZE_TILE_H, SIZE_TILE_W,SIZE_TILE_H, 0);
            if(map[x][y].getID() == 1)
                al_draw_scaled_bitmap(TILE_terrain[1], 0,0, getBmpW(TILE_terrain[1]),getBmpW(TILE_terrain[1]),
                                      x*SIZE_TILE_W,y*SIZE_TILE_H, SIZE_TILE_W,SIZE_TILE_H, 0);
        }
}
