#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "main.h"

class CCamera {
    float x, y, zoom;
    float startX, startY;
    ALLEGRO_TRANSFORM coord;

public:

    CCamera();
    ~CCamera();

    inline float getX() { return x; }
    inline float getY() { return y; }
    inline float getZoom() { return zoom; }

    void setPos(float,float); // zmienia pozycje
    void setStart(float,float); // pozycja poczatkowa
    void addPos(float,float); // dodaje polozenie do aktualnej pozycji

    void setZoom(float);

    template <class Arg>
    Arg follow(Arg); // sledzi jakis obiekt, np gracza (musi miec zmienne pos.x, pos.y, w, h)

    void update();
    void reset();
};

template <class Arg>
Arg CCamera::follow(Arg a) {
    x = a->pos.x + a->w/2 - 400;
    y = a->pos.y + a->h/2 - 300;
}

#endif // CAMERA_H_INCLUDED
