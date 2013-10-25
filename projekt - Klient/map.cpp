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
}

CMap::~CMap() {
    for(int i = 0; i < w; i++)
        delete[] map[i];

    delete[] map;
}

void CMap::resize(int w2, int h2) {
    this->w = w2;
    this->h = h2;

    map = new CTile*[w];
    for(int i = 0; i < w; ++i)
        map[i] = new CTile[h];
}

void CMap::createMap(ENetPacket* packet) {
    int end = 0, index = 0;
    bool byloX = false;
    string map_w = "", map_h = "", map_file = "";

    for(int i = 0; i < packet->dataLength-1; ++i) {
        if(packet->data[i] == ' ') {
            end = i;
            break;
        }

        if(packet->data[i] != 'x') {
            if(!byloX) {
                map_w.resize(map_w.size()+1);
                map_w[index] = packet->data[i];
                ++index;
            }
            else {
                map_h.resize(map_h.size()+1);
                map_h[index] = packet->data[i];
                ++index;
            }
        }
        else {
            index = 0;
            byloX = true;
        }
    }

    int map_wInt = atoi(map_w.c_str());
    int map_hInt = atoi(map_h.c_str());

    for(int i = end; i < packet->dataLength-1; ++i) {
        map_file.resize(map_file.size()+1);
        map_file[i-end] = packet->data[i];
    }

    resize(map_wInt, map_hInt);

    getMapFromString(map_file);
}

void CMap::getMapFromString(string file) {
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

void CMap::render(CCamera* camera) {
    camera->update();

    for(int x = 0; x < w; ++x)
        for(int y = 0; y < h; ++y) {
            if(map[x][y].getID() == 0)
                al_draw_scaled_bitmap(TILE_terrain[0], 0,0, getBmpW(TILE_terrain[0]),getBmpW(TILE_terrain[0]),
                                      x*SIZE_TILE_W,y*SIZE_TILE_H, SIZE_TILE_W,SIZE_TILE_H, 0);
            if(map[x][y].getID() == 1)
                al_draw_scaled_bitmap(TILE_terrain[1], 0,0, getBmpW(TILE_terrain[1]),getBmpW(TILE_terrain[1]),
                                      x*SIZE_TILE_W,y*SIZE_TILE_H, SIZE_TILE_W,SIZE_TILE_H, 0);
        }

    camera->reset();
}
