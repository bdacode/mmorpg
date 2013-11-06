#ifndef MAP_OBJ_H_INCLUDED
#define MAP_OBJ_H_INCLUDED

#include "main.h"

class CMapObject {
public:

    float x, y,
          scalX, scalY,
          angle;

    CMapObject();
};

extern vector <CMapObject> v_mapObj;

void loadObj();
void renderObj();


#endif // MAP_OBJ_H_INCLUDED
