#include "map.h"

CMap::CMap(){
    w = h = 10;
}

CMap::CMap(int w, int h)
    : w(w), h(h){
    CTile** map = new CTile*[w];
    for(int i = 0; i < w; ++i)
        map[i] = new CTile[h];
}

CMap::~CMap(){
    for(int i = 0; i < w; i++)
        delete[] map[i];

    delete[] map;
}

void CMap::load(){

}

void CMap::render(){

}
